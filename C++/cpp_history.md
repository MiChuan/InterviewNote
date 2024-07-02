# C++ 发展历史

## 简要年表

- 1979年，基于C语言实现了C++的前身：C with Classes
- 1983年，正式命名为C++。
- 1990年，C++标准委员会成立，C++标准化进程开始。
- 1994年，委员会完成草案登记。
- 1998年，发布C++98，第一个C++正式标准。
- 2003年，发布C++03，对C++98仅有很少的修订。
- 2011年，发布C++11，是C++标准的重大升级，增加大量新特性。
- 2014年，发布C++14，小幅度扩充了C++11标准。
- 2017年，发布C++17，对C++14再做修订，主要增强了标准库。
- 2020年，发布C++20，增加了概念、模块、协程等重磅特性，堪比C++11。

### C++98
C++98标准是C++的第一个国际标准，与早期的C++相比，它有了重大进步

### C++11
- 新的nullptr关键字，取代了容易引起错误的NULL宏或0。
- 新的noexcept关键字，取代了原有的异常规范。
- 新的constexpr关键字，编译期常量表达式，有利于模板元编程。
- 新的auto/decltype关键字，可以自动推导类型声明。
- 新的default和delete用法，可以明确地控制函数的实现（默认或禁用）。
- 新的for循环语法，可以更容易地遍历容器，代码更简洁。
- 原始（raw）字符串，用形如R＂（...）＂的方式来书写字符串，不必用“\”转义。
- 右值引用、完美转发和转移（move）语义，可以更高效地返回对象。
- 可变参数模板，可以更容易地编写泛型代码，不必使用晦涩的预处理。
- 语言级别的lambda表达式，可以非常容易地编写匿名函数对象。
- 废弃了异常规范、auto_ptr和关键字export、register。
- 极大地增强了标准库，添加了许多新的组件，其中有数个基于Boost，如array、bind、function、random、shared_ptr、thread、tuple等。

### C++14
- 模板变量，如template＜typename T＞T val。
- 属性[[deprecated]]，用于声明废弃的对象、函数或类。
- 新的decltype（auto）类型推导语法。
- 泛型lambda表达式，可以用auto声明入口参数。
- 使用auto关键字自动推导函数返回类型。
- 使用单引号（＇）作为数字分位符。
- “0b/0B”格式的二进制字面值。
- 时、分、秒（h/min/s）等预定义字面值。
- 用于创建unique_ptr的工厂函数make_unique。

### C++17
- 检查是否已经包含了头文件的宏__has_include。
- 简化的嵌套名字空间定义，如namespace a：：b：：c。
- std：：invoke（），统一的函数调用方式。
- std：：apply（），使用tuple发起函数调用，基于std：：invoke（）。
- 并行算法，可以传入参数std：：execution：：par显式要求并行处理。
- 无效值包装器optional，基于boost.optional。
- 字符串引用string_view，基于boost.string_ref。
- 支持UTF-8编码的字符串，如u8＂string＂。
- 增强的联合体variant，基于boost.variant。
- 操纵文件系统的filesystem，几乎与boost.filesystem相同。

### C++20
- range：类似boost.range，可以用“|”串联起多个算法。- span：类似string_view，是序列容器的子视图。
- module：取代include语句，更“现代化”的模块机制。
- coroutine：语言级别的协程功能。
- concurrency：语言级别的并发支持。
- concept：重新设计、精简后的概念检查库。
- networking：标准内置的网络开发库。