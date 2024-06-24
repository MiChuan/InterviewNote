# Redis 数据结构

## Redis 基本数据结构

Redis 有 5 种数据结构：string (字符串)、list (列表)、set (集合)、hash (哈希) 和 zset (有序集合)。

### string

Redis 所有的数据结构都是以唯一的 key 字符串作为名称，然后通过这个唯一 key 值来获取相应的 value 数据。不同类型的数据结构的差异就在于 value 的结构不一样。

### list

链表。当列表弹出了最后一个元素之后，该数据结构自动被删除，内存被回收。

### hash

字典的值只能是字符串。

### set

相当于一个特殊的字典，字典中所有的 value 都是一个值 NULL。

### zset

一个 set，保证了内部 value 的唯一性，另一方面它可以给每个 value 赋予一个 score，代表这个 value 的排序权重。它的内部实现用的是一种叫着**跳跃列表**的数据结构。

## SDS

> Redis 封装了一个简单动态字符串（simple dynamic string，SDS） 的数据结构来表示字符串。

| 字段  | 解释           |
| ----- | -------------- |
| len   | 字符串长度     |
| alloc | 分配的空间长度 |
| flags | sds类型        |
| buf[] | 字节数组       |

## 链表

```cpp
typedef struct listNode {
     //前置节点
     struct listNode *prev;
     //后置节点
     struct listNode *next;
     //节点的值
     void *value;
} listNode;

typedef struct list {
     //链表头节点
     listNode *head;
     //链表尾节点
     listNode *tail;
     //节点值复制函数
     void *(*dup)(void *ptr);
     //节点值释放函数
     void (*free)(void *ptr);
     //节点值⽐较函数
     int (*match)(void *ptr, void *key);
     //链表节点数量
     unsigned long len;
} list;
```

Redis 3.0 的 List 对象在数据量⽐较少的情况下，会采⽤「压缩列表」作为底层数据结构的实现，它的优势是节省内存空间，并且是内存紧凑型的数据结构。不过，压缩列表存在性能问题，所以 Redis 在 3.2 版本设计了新的数据结构 quicklist，并将 List 对象的底层数据结构改由 quicklist 实现。然后在 Redis 5.0 设计了新的数据结构 listpack，沿⽤了压缩列表紧凑型的内存布局，最终在最新的 Redis 版本，将 Hash 对象和 Zset 对象的底层数据结构实现之⼀的压缩列表，替换成由 listpack 实现。

## 哈希表

Redis 采⽤了「链式哈希」来解决哈希冲突。

```cpp
typedef struct dictEntry {
     //键值对中的键
     void *key;
 
     //键值对中的值
     union {
     	void *val;
     	uint64_t u64;
     	int64_t s64;
     	double d;
     } v;
     //指向下⼀个哈希表节点，形成链表
     struct dictEntry *next;
} dictEntry;
 
typedef struct dictht {
     //哈希表数组
     dictEntry **table;
     //哈希表⼤⼩
     unsigned long size; 
     //哈希表⼤⼩掩码，⽤于计算索引值
     unsigned long sizemask;
     //该哈希表已有的节点数量
     unsigned long used;
} dictht;
```

## 整数集合

Set 对象的底层实现之⼀。

```cpp
typedef struct intset {
	//编码⽅式
	uint32_t encoding;
	//集合包含的元素数量
	uint32_t length;
	//保存元素的数组
	int8_t contents[];
} intset;
```

## 跳表

Redis 只有在 Zset 对象的底层实现⽤到了跳表，跳表的优势是能⽀持平均 O(logN) 复杂度的节点查找。

1. Zset 对象在使⽤压缩列表作为底层数据结构的时候，zset对象结构的指针会指向压缩列表；
2. Zset对象在使⽤跳表作为底层数据结构的时候，zset对象结构的指针会指向zset结构（哈希表+跳表）。

```cpp
typedef struct zset {
	dict *dict;
	zskiplist *zsl;
} zset;

typedef struct zskiplistNode {
	//Zset 对象的元素值
	sds ele;
	//元素权重值
	double score;
	//后向指针
	struct zskiplistNode *backward;
 
	//节点的level数组，保存每层上的前向指针和跨度
	struct zskiplistLevel {
 		struct zskiplistNode *forward;
		unsigned long span;
	} level[];
} zskiplistNode;

typedef struct zskiplist {
	struct zskiplistNode *header, *tail;
	unsigned long length;
	int level;
} zskiplist;
```

## quicklist

 Redis 3.2 的时候，List 对象的底层改由 quicklist 数据结构实现。quicklist 就是「双向链表 + 压缩列表」组合，⼀个 quicklist 就是⼀个链表，⽽链表中的每个元素⼜是⼀个压缩列表。

```cpp
typedef struct quicklist {
	//quicklist的链表头
	quicklistNode *head; //quicklist的链表头
	//quicklist的链表头
	quicklistNode *tail;
	//所有压缩列表中的总元素个数
	unsigned long count;
	//quicklistNodes的个数
	unsigned long len; 
	...
} quicklist;

typedef struct quicklistNode {
	//前⼀个quicklistNode
	struct quicklistNode *prev; //前⼀个quicklistNode
	//下⼀个quicklistNode
	struct quicklistNode *next; //后⼀个quicklistNode
	//quicklistNode指向的压缩列表
	unsigned char *zl; 
	//压缩列表的的字节⼤⼩
	unsigned int sz; 
	//压缩列表的元素个数
	unsigned int count : 16; //ziplist中的元素个数
	....
} quicklistNode;
```

## listpack

Redis 在 5.0 新设计⼀个数据结构叫 listpack，⽬的是替代压缩列表。

listpack 结构：

| listpack 总字节数 | listpack 元素数量 | listpack entry | listpack entry | listpack entry | listpack 结尾标识 |
| ----------------- | ----------------- | -------------- | -------------- | -------------- | ----------------- |

listpack 节点结构：

| encoding | data | len  |
| -------- | ---- | ---- |

- encoding，定义该元素的编码类型，会对不同⻓度的整数和字符串进⾏编码；

- data，实际存放的数据；

- len，encoding+data的总⻓度；