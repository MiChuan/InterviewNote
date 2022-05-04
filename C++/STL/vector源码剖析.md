# vector源码剖析

[toc]

## 定义

**定义**：封装动态数组的顺序容器。

```cpp
template<
  class T, 
  class Allocator = std::allocator<T>
> class vector;
```

**模板参数 **

- T 必须满足可拷贝赋值(CopyAssignable)和可拷贝构造(CopyConstructible)的要求。
- Allocator 用于获取/释放内存及构造/析构内存中元素的分配器。类型必须满足分配器(Allocator)的要求。若Allocator: :value_tvpe与T不同则行为未定义。

**常见操作复杂度**

- 随机访问——常数 O(1)
- 在末尾插入或移除元素——均摊常数 O(1)
- 插入或移除元素——与到 vector 结尾的距离成线性 O(n)

## 成员类型

| 成员类型                 | 定义                                                         |
| ------------------------ | ------------------------------------------------------------ |
| `value_type`             | `T`                                                          |
| `allocator_type`         | `Allocator`                                                  |
| `size_type`              | 无符号整数类型                                               |
| `difference_type`        | 有符号整数类型                                               |
| `reference`              | Allocator::reference, value_type&                            |
| `const_reference`        | Allocator::const_reference, const value_type&                |
| `pointer`                | Allocator::pointer, std::allocator_traits<Allocator>::pointer |
| `const_pointer`          | Allocator::const_pointer, std::allocator_traits<Allocator>::const_pointer |
| `iterator`               | 随机访问迭代器 (RandomAccessIterator)                        |
| `const_iterator`         | 常随机访问迭代器                                             |
| `reverse_iterator`       | std::reverse_iterator<iterator>                              |
| `const_reverse_iterator` | std::reverse_iterator<const_iterator>                        |

## 成员函数

### 特殊函数

| 函数名        | 函数功能       |
| ------------- | -------------- |
| 构造函数      | 构造vector     |
| 析构函数      | 析构vector     |
| operator=     | 赋值给容器     |
| assign        | 将值赋值给容器 |
| get_allocator | 返回分配器     |

**构造函数**

```cpp
// 列表初始化
std::vector<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
// 区间初始化
std::vector<std::string> words2(words1.begin(), words1.end());
// 拷贝构造
std::vector<std::string> words3(words1);
// 初始化构造多个相同值
std::vector<std::string> words4(5, "Mo");
```

**assign**

```cpp
// 赋值多个相同值
void assign(size_type count, const T& value);
// 赋值列表
template<class InputIt>
void assign(InputIt first, InputIt last);
void assign(std::initializer_list<T> ilist);
```

### 元素访问

| 函数名     | 函数功能                           |
| ---------- | ---------------------------------- |
| at         | 访问指定的元素，同时进行越界检查   |
| operator[] | 下标索引访问指定的元素             |
| front      | 获得第一个元素迭代器               |
| back       | 获得最后一个元素迭代器             |
| data       | 返回指向内存中数组第一个元素的指针 |

### 迭代器

| 函数名          | 函数功能                         |
| --------------- | -------------------------------- |
| begin，cbegin   | 返回指向容器第一个元素的迭代器   |
| end，cend       | 返回指向容器尾端的迭代器         |
| rbegin，rcbegin | 返回指向容器最后元素的逆向迭代器 |
| rend，rcend     | 返回指向前端的逆向迭代器         |

### 容量

| 函数名        | 函数功能                         |
| ------------- | -------------------------------- |
| empty         | 检查容器是否为空                 |
| size          | 返回容纳的元素数                 |
| max_size      | 返回可容纳的最大元素数           |
| reserve       | 预留存储空间                     |
| capacity      | 返回当前存储空间能够容纳的元素数 |
| shrink_to_fit | 释放未使用的内存减少内存的使用   |

### 修改器

| 函数名       | 函数功能                   |
| ------------ | -------------------------- |
| clear        | 清除内容                   |
| insert       | 插入元素                   |
| emplace      | 原位构造元素               |
| erase        | 擦除元素                   |
| push_back    | 将元素添加到容器末尾       |
| emplace_back | 在容器末尾就地构造元素     |
| pop_back     | 移除末元素                 |
| resize       | 改变容器中可存储元素的个数 |
| swap         | 交换内容                   |

**insert**

```cpp
// 插入一个值
iterator insert(iterator pos, const T& value);
iterator insert(const_iterator pos, const T& value);
iterator insert(const_iterator pos, T&& value);
// 插入多个相同值
void insert(iterator pos, size_type count, const T& value);
iterator insert(const_iterator pos, size_type count, const T& value);
// 插入列表
template<class InputIt>
void insert(iterator pos, InputIt first, InputIt last);
template<class InputIt>
iterator insert(const_iterator pos, InputIt first, InputIt last);
iterator insert(const_iterator pos, std::initializer_list<T> ilist);
```

**erase**

```
// 移除位于 pos 的元素
iterator erase(iterator pos);
iterator erase(const_iterator pos);
// 移除范围 [first; last) 中的元素
iterator erase(iterator first, iterator last);
iterator erase(const_iterator first, const_iterator last);
```

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