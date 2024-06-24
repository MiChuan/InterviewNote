# Linux模块化增加设备驱动程序

## 目录

[toc]

## 目的

1. 采用模块方法，添加一个新的字符设备驱动程序，实现打开/关闭、读/写等基本操作
2. 编写一个应用程序，测试添加的驱动程序

## 开发环境

- 操作系统: ubuntu 16.04LTS 64位
- 内核版本:linux-4.14.141
- 内存:8G
- 处理器: IntelR CoreTM i5-6200U CPU@ 2.30GHz×4
- 编辑器: Vim
- 编译器: gcc version 5.4.0 20160609

## 实验步骤

1. 编写**设备驱动程序源文件**`mydev.c`
2. 编写`Makefile`文件，用于执行**编译任务**
3. 将设备驱动程序源文件和Makefile文件拷贝到`/usr/src/linux-4.14.141/drivers/misc/mydev`目录下，在该目录打开终端
4. 执行`make`命令,利用Makefile文件进行设备驱动模块**编译**，编译成功后生成`mydev.ko`文件
5. 执行`insmod mydev.ko`，加载设备驱动模块
6. 通过`lsmod`命令查看模块是否加载成功，通过`cat /proc/devices`命令查看**新增设备名**mydev和**主设备号**241
7. 进入`/dev`目录，执行命令`mknod /dev/mydev c 241 0`，生成设备文件，其中，mydev为**设备文件名**，241为**主设备号**，0为**从设备号**，c表示**字符设备**，执行成功后在/dev目录中会生成一个**新设备文件**
8. 编译**测试程序**，执行并进行测试

## 关键代码

### 打开设备

1. 通过 MAJOR和MINOR返回主次设备号：

   ```c
   printk("mydev: Main device number is %d  \n Slave device number is %d\n", MAJOR(inode->i_rdev), MINOR(inode->i_rdev));
   ```

2. 使用静态变量保存打开设备的进程数：

   ```c
   static int open_process = 0;
   ```

3. 当设备未被占用，占有设备，当设备被占用，进程挂起：

```c
 // 未被占用
if (open_process == 0) {
    open_process++; //标志占用
    try_module_get(THIS_MODULE);
    return 0;
} else {// 被占用
    printk(KERN_ALERT "Another process open the char device.\n"); 
    //进程挂起
    return -1;
}
```

### 释放设备，解除占用

```c
--open_process; //占用解除
module_put(THIS_MODULE);
```

### 读取设备缓冲区内容到终端

从内核拷贝数据到用户空间，调用内核函数copy_to_user

```c
copy_to_user(buf, buffer, sizeof(buffer);
```

### 输入字符串，从终端读取，写入设备缓冲区

数据从用户空间拷贝到内核，调用内核函数copy_from_user

```c
copy_from_user(buffer, buf, sizeof(buffer);
```

### 注册字符设备

```c
result = register_chrdev(DEVICE_NUM, "mydev", &mydev_fops);
```

### 注销字符设备

```c
unregister_chrdev(device_num, "mydev");
```

### 添加模块宏定义和许可协议

```c
//模块宏定义
module_init(mydev_init);
module_exit(mydev_exit);
// 模块许可协议
MODULE_LICENSE("GPL");
```

## 调试记录

1. 使用`Makefile文件`**编译**设备驱动模块

![编译设备驱动模块](http://mi_chuan.gitee.io/blog/编译设备驱动模块.png)

2. 执行`insmod mydev.ko`，**加载设备驱动模块**

![加载设备驱动模块](http://mi_chuan.gitee.io/blog/加载设备驱动模块.png)

3. 通过`cat /proc/devices`命令查看新增**设备名mydev**和**主设备号**

![查看设备驱动模块设备号](http://mi_chuan.gitee.io/blog/查看设备驱动模块设备号.png)

4. 执行命令`mknod /dev/mydev c 241 0`，生成**设备文件**，查看设备文件

![生成设备文件](http://mi_chuan.gitee.io/blog/生成设备文件.png)

5. 编译**测试程序**，执行并进行测试

![编译运行测试程序](http://mi_chuan.gitee.io/blog/编译运行测试程序.png)

## 测试代码目录说明

**开源地址**：[OS_Kernel/compile_kernel&add_syscall](https://github.com/MiChuan/OS_Kernel/tree/master/modularly_add_device_drivers)

> modularly_add_device_drivers    模块化添加驱动设备源文件目录
>
> > Linux模块化增加设备驱动程序.md
> >
> > help.txt           Makefile与make命令参考
> >
> > Makefile          make编译脚本
> >
> > mydev.c          驱动程序源文件
> >
> > test                  测试程序
> >
> > test.c               测试程序源代码