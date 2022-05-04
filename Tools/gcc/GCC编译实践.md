## GCC文件扩展名

| 文件名称+扩展名                                              | GCC 编译器识别的文件类型                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| **file.c**                                                   | 尚未经过预处理操作的 C 源程序文件。                          |
| file.i                                                       | 经过预处理操作、但尚未进行编译、汇编和连接的 C 源代码文件。  |
| **file.cpp** file.cp file.cc file.cxx file.CPP file.c++ file.C | 尚未经过预处理操作的 C++ 源代码文件。                        |
| file.ii                                                      | 已经预处理操作，但尚未进行编译、汇编和连接的 C++ 源代码文件。 |
| file.s                                                       | 经过编译生成的汇编代码文件。                                 |
| **file.h**                                                   | C、C++ 或者 Objective-C++ 语言头文件。                       |
| file.hh file.H file.hp file.hxx file.hpp file.HPP file.h++ file.tcc | C++ 头文件。                                                 |

## 编译标准

使用 gcc 指令编译 C 语言程序时，可以借助 -std 选项指定要使用的编译标准；同样，当使用 g++ 指令编译 C++ 程序时，也可以借助 -std 选项指定要使用的编译标准。

```bash
$ gcc/g++ -std=编译标准
$ gcc/g++ -std=c11
```

## 编译过程

### 预处理

预处理是 C 语言程序从源代码变成可执行程序的第一步，主要是 C 语言编译器对各种预处理命令进行处理，包括头文件的包含、宏定义的扩展、条件编译的选择等。

**打印出预处理之后的结果**

```bash
$ gcc -E hello.c
```

**在命令行定义宏**

```bash
$ gcc -DMYDEBUG hello.c
```

等同于在文件的开头定义宏，即 #define MYDEBUG，但是在命令行定义更灵活。例如，在源代码中有这些语句。

```bash
#ifdef MYDEBUG
	printf("this code is for debugging\n");
#endif
```

如果编译时加上 -DDEBUG 选项，那么编译器就会把 printf 所在的行编译进目标代码，从而方便地跟踪该位置的某些程序状态。这样 -DMYDEBUG就可以当作一个调试开关，编译时加上它就可以用来打印调试信息，发布时则可以通过去掉该编译选项把调试信息去掉。

**常用选项**

| 选 项                       | 功 能                                                        |
| --------------------------- | ------------------------------------------------------------ |
| **-Dname [=definition]**    | 在处理源文件之前，先定义宏 name。宏 name 必须是在源文件和头文件中都没有被定义过的。将该选项搭配源代码中的#ifdef name命令使用，可以实现条件式编译。如果没有指定一个替换的值（即省略 =definition），该宏被定义为值 1。 |
| -U name                     | 如果在命令行或 GCC 默认设置中定义过宏 name，则“取消”name 的定义。-D 和 -U 选项会依据在命令行中出现的先后顺序进行处理。 |
| **-include file**           | 如同在源代码中添加 #include “file” 一样。                    |
| **-iquote dir**             | 对于以引号（#include “”）导入的头文件中，-iquote 指令可以指定该头文件的搜索路径。当 GCC 在源程序所在目录下找不到此头文件时，就会去 -iquote 指令指定的目录中查找。 |
| **-I dir**                  | 同时适用于以引号 “” 和 <> 导入的头文件。当 GCC 在 -iquote 指令指定的目录下搜索头文件失败时，会再自动去 -I 指定的目录中查找。该选项在 GCC 10.1 版本中已被弃用，并建议用 -iquote 选项代替。 |
| -isystem dir -idirafter dir | 都用于指定搜索头文件的目录，适用于以引号 “” 和 <> 导入的头文件。 |

其中，对于指定 #include 搜索路径的几个选项，作用的先后顺序如下：

- 对于用 #include “” 引号形式引入的头文件，首先搜索当前程序文件所在的目录，其次再前往 -iquote 选项指定的目录中查找；
- 前往 -I 选项指定的目录中搜索；
- 前往 -isystem 选项指定的目录中搜索；
- 前往默认的系统路径下搜索；
- 前往 -idirafter 选项指定的目录中搜索。

### 编译

编译之前，C 语言编译器会进行词法分析、语法分析，接着会把源代码翻译成中间语言，即汇编语言。如果想看到这个中间结果，可以用 `gcc -S`。需要提到的是，诸如 Shell 等解释语言也会经历一个词法分析和语法分析的阶段，不过之后并不会进行“翻译”，而是“解释”，边解释边执行。

```bash
$ gcc -S test.cpp

$ ls
test.cpp  test.s

$ cat test.s
        .file   "test.cpp"
        .def    ___main;        .scl    2;      .type   32;     .endef
        .section .rdata,"dr"
LC0:
        .ascii "hello\0"
        .text
        .globl  _main
        .def    _main;  .scl    2;      .type   32;     .endef
_main:
LFB12:
        .cfi_startproc
        pushl   %ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        movl    %esp, %ebp
        .cfi_def_cfa_register 5
        andl    $-16, %esp
        subl    $16, %esp
        call    ___main
        movl    $LC0, (%esp)
        call    _puts
        movl    $0, %eax
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE12:
        .ident  "GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
        .def    _puts;  .scl    2;      .type   32;     .endef
```

### 汇编

```bash
$ gcc -c test.cpp
$ ls
test.cpp  test.o
```

### 链接

```bash
$ gcc -o test test.cpp
$ ls
test.cpp  test.exe*
```

**手动添加链接库**

```bash
$ gcc main.c -o main.out -lm
```

数学库的文件名是 libm.a。前缀 lib 和后缀 .a 是标准的，m 是基本名称，GCC 会在 -l 选项后紧跟着的基本名称的基础上自动添加这些前缀、后缀，本例中，基本名称为 m。

**链接其它目录中的库**

通常，GCC 会自动在标准库目录中搜索文件，例如 /usr/lib，如果想链接其它目录中的库，就得特别指明。有三种方式可以链接在 GCC 搜索路径以外的链接库，下面我们分别讲解。

1. 把链接库作为一般的目标文件，为 GCC 指定该链接库的完整路径与文件名。例如，如果链接库名为 libm.a，并且位于 /usr/lib 目录，那么下面的命令会让 GCC 编译 main.c，然后将 libm.a 链接到 main.o：

   ```bash
   $ gcc main.c -o main.out /usr/lib/libm.a
   ```

2. 使用 -L 选项，为 GCC 增加另一个搜索链接库的目录：

   ```bash
   $ gcc main.c -o main.out -L/usr/lib -lm
   ```

   可以使用多个 -L 选项，或者在一个 -L 选项内使用冒号分割的路径列表。

3. 把包括所需链接库的目录加到环境变量 LIBRARYPATH 中。

## 参考资料

[GCC教程](https://haicoder.net/gcc/gcc-tutorial.html)