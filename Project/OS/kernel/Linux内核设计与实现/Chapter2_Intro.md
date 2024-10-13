# Chapter-2 Introduction

## 内核源码树

|      目录      |        描述        |
| :------------: | :----------------: |
|      arch      |    特定体系结构    |
|     block      |       块设备       |
|     crypto     |        加密        |
| Documentatrion |        文档        |
|    drivers     |      设备驱动      |
|    firmware    |      设备固件      |
|       fs       |      文件系统      |
|    include     |     内核头文件     |
|      init      |  内核引导和初始化  |
|      ipc       |     进程间通信     |
|     kernel     |     核心子系统     |
|      lib       |    通用内核函数    |
|       mm       | 内存管理子系统和VM |
|      net       |     网络子系统     |
|    samples     |      示例代码      |
|    scripts     |        脚本        |
|    security    |      安全模块      |
|     sound      |     语音子系统     |
|      usr       |  早期用户空间代码  |
|     tools      |        工具        |
|      virt      |       虚拟化       |

## 内核开发的特点

- 内核编程时必须使用 GNU C，C99 标准
- 内核编程时缺乏像用户空间那样的内存保护机制
- 内核编程时难以执行浮点运算
- 内核给每个进程只有一个很小的定长堆栈
- 由于内核支持异步中断、抢占和 SMP，因此必须时刻注意同步和并发
- 要考虑可移植性的重要性