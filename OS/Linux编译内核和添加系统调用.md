# Linux编译内核和添加系统调用

[toc]

## 目的

1. 采用编译内核的方法，添加一个新的系统调用，实现文件拷贝功能

2. 编写一个应用程序，测试新加的系统调用

## 环境和步骤

### 开发环境

- 操作系统：ubuntu 16.04 LTS 64位
- 内核版本：linux-4.14.141
- 内存：8G
- 处理器：Intel® Core™ i5-6200U CPU @ 2.30GHz × 4 
- 编辑器：Vim
- 编译器：gcc version 5.4.0

### 步骤

1. 下载内核源码并解压，下载版本为linux-4.14.141

2. 编写添加到内核中的新的系统调用例程，将例程添加到linux-4.14.141/kernel/sys.c文件中

3. 连接新的系统调用，在linux-4.14.141/include/linux/syscalls.h文件中添加新的系统调用的函数定义，在linux-4.14.141/arch/x86/entry/syscalls/syscall_64.tbl系统调用表中为新增的系统调用分配一个系统调用号和系统调用名

4. 配置编译内核所需环境

```shell
$ sudo apt-get install libncurses* 
$ sudo apt-get install build-essential openssl 
$ sudo apt-get install zlibc minizip 
$ sudo apt-get install libidn11-dev libidn11
```

5. 将内核源码拷贝到/usr/src目录下，进入内核源码目录，在该目录打开终端，进入超级用户权限
6. 生成配置文件.config，在终端执行

```shell
$ make menuconfig
```

7. 多线程编译内核

```shell
$ make -j8
```

8. 生成并安装模块

```shell
$ make modules_install
```

9. 安装新系统

```shell
$ make install
```

10. 重启，选择新修改的内核

11. 编写应用程序，测试新增的系统调用

## 核心代码

### 添加系统调用例程

1. 函数定义使用了宏定义SYSCALL_DEFINEx，x代表参数数目，新增例程需传入2个参数，故x为2；宏定义第一个参数为系统调用名mycopy，而后为参数类型申明const char __user *，__user标记了参数是从用户空间传入，即传入的文件名，故函数定义为：

```c
SYSCALL_DEFINE2(mycopy, const char __user *, _target, const char __user *, _source)
```

2. 系统调用提供了用户程序和操作系统之间的接口，应用程序通过系统调用实现其与 OS 的通信，并可取得它的服务。故系统调用总数默认传入参数来自用户空间，此时在内核中调用内核函数传入参数，则需要将用户空间参数拷贝到内核空间，防止因KPTI（内核页表隔离）产生访问错误，调用函数strndup_user将文件名从用户空间拷贝到内核空间：

```c
target = strndup_user(_target,PAGE_SIZE);
source = strndup_user(_source,PAGE_SIZE);
```

3. 调用`sys_open`，`sys_read`，`sys_write`函数时，为保护内核空间，会首先对参数进行检查，为防止发生段错误，需要通过设置`set_fs(KERNEL_DS)`将其能访问的空间限制扩大到内核空间，在完成内核函数调用返回用户空间时，需恢复成原来的访问范围：


```c
mm_segment_t fs;
fs = get_fs();     //get access restriction value
set_fs(get_ds());  //set kernel restriction value
```

   返回之前恢复：

```c
// close file
sys_close(tar_fd);
sys_close(sor_fd);
set_fs(fs);  //recovery
```

### syscalls.h文件中添加新增系统调用例程函数声明

```c
asmlinkage long sys_mycopy(const char __user *target, const char __user *source);
```

### syscall_64.tbl系统调用表中添加新增系统调用号

```bash
# mycalls 
333 64  hello_world     sys_hello_world
334 64  mycopy          sys_mycopy
```

## 测试

1. 使用uname -r命令查看当前系统内核版本

   ![查看内核版本](http://mi_chuan.gitee.io/blog/查看内核版本.png)

2. gcc编译测试程序并运行

   ![测试系统调用](http://mi_chuan.gitee.io/blog/测试系统调用.png)

## 测试代码目录说明

**开源地址**：[OS_Kernel/compile_kernel&add_syscall](https://github.com/MiChuan/OS_Kernel/tree/master/compile_kernel%26add_syscall)

> compile_kernel&add_syscall    编译内核和添加系统调用代码目录
>
> > Linux编译内核和添加系统调用.md
> >
> > test_pro             测试程序文件夹
> >
> > > IOT                 测试源文件
> > >
> > > IOT1               拷贝结果
> > >
> > > test_copy.c    测试源程序代码
> > >
> > > test_copy       编译生成的二进制程序
> >
> > ReadMe.txt        内核空间访问说明
> >
> > syscall_64.tbl     系统调用表
> >
> > syscalls.h            系统调用头文件
> >
> > sys.c                    系统调用函数定义源文件
> >
> > test_copy.c         测试自定义拷贝系统调用源程序代码
> >
> > test_hello.c         测试自定义打印"hello"的系统调用
> >
> > mycopy.c            需要修改的文件内容总结
