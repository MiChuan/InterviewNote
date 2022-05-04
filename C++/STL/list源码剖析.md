# list源码剖析

[toc]

## 定义

**定义**：支持常数时间从容器任何位置插入和移除元素的容器。不支持快速随机访问。通常实现为双向链表。

```cpp
template<
  class T,
  class Allocator = std::allocator<T>
> class list;
```

### 模板参数

- T - 必须满足可拷贝赋值 (CopyAssignable) 和可拷贝构造 (CopyConstructible) 的要求。

- Allocator - 用于获取/释放内存及构造/析构内存中元素的分配器。类型必须满足分配器 (Allocator) 的要求。 

## 成员函数

### 特殊函数

| 函数名        | 函数功能       |
| ------------- | -------------- |
| 构造函数      | 构造list       |
| 析构函数      | 析构list       |
| operator=     | 赋值给容器     |
| assign        | 将值赋值给容器 |
| get_allocator | 返回分配器     |

**构造函数**

```cpp
std::list<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
std::list<std::string> words2(words1.begin(), words1.end());
std::list<std::string> words3(words1);
std::list<std::string> words4(5, "Mo");
```

**assign**

### 元素访问

| 函数名 | 函数功能               |
| ------ | ---------------------- |
| front  | 获得第一个元素迭代器   |
| back   | 获得最后一个元素迭代器 |

### 迭代器

| 函数名          | 函数功能                         |
| --------------- | -------------------------------- |
| begin，cbegin   | 返回指向容器第一个元素的迭代器   |
| end，cend       | 返回指向容器尾端的迭代器         |
| rbegin，rcbegin | 返回指向容器最后元素的逆向迭代器 |
| rend，rcend     | 返回指向前端的逆向迭代器         |

### 容量

| 函数名   | 函数功能               |
| -------- | ---------------------- |
| empty    | 检查容器是否为空       |
| size     | 返回容纳的元素数       |
| max_size | 返回可容纳的最大元素数 |

### 修改器

| 函数名        | 函数功能                   |
| ------------- | -------------------------- |
| clear         | 清除内容                   |
| insert        | 插入元素                   |
| emplace       | 原位构造元素               |
| erase         | 擦除元素                   |
| push_back     | 将元素添加到容器末尾       |
| emplace_back  | 在容器末尾就地构造元素     |
| pop_back      | 移除末元素                 |
| push_front    | 插入元素到容器起始         |
| emplace_front | 在容器头部就地构造元素     |
| pop_front     | 移除首元素                 |
| resize        | 改变容器中可存储元素的个数 |
| swap          | 交换内容                   |

### 操作

| 函数名            | 函数功能                     |
| ----------------- | ---------------------------- |
| merge             | 合并二个已排序列表           |
| splice            | 从另一个`list`中移动元素     |
| remove，remove_if | 移除满足特定标准的元素       |
| reverse           | 将该链表的所有元素的顺序反转 |
| unique            | 删除连续的重复元素           |
| sort              | 对元素进行排序               |

## 非成员函数

| 函数名     | 函数功能                       |
| ---------- | ------------------------------ |
| operator== | 按照字典顺序比较 vector 中的值 |
| operator!= |                                |
| operator<  |                                |
| operator<= |                                |
| operator>  |                                |
| operator>= |                                |

## 参考资料

[cppreference](https://qingcms.gitee.io/cppreference/20210212/zh/)

《STL源码剖析》