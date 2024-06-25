# Qt 多线程

> Qt 中的多线程使用方式有两种。一是直接继承 QThread，重写 QThread 中的 run() 函数；另外一种是利用 QObject 原有的 moveToThread() 函数，通过事件驱动的方式启用多线程。

## QThread

`workthread.h`

```cpp
#include <QThread>
#include <QDebug>
class WorkThread : public QThread//继承Qt中的线程类
{
public:
     WorkThread();
public:
     void run();//重写run()函数
};
```

`workthread.cpp`

```cpp
void WorkThread::run()
{
    for(;;) {
        qDebug()<< "WorkThread："<<QThread::currentThreadId();
        sleep(1);
    }
}
```

`main.cpp`

```cpp
#include "workthread.h"
int main(int argc, char *argv[])
{
     WorkThread wt1,wt2;
     wt1.start();
     wt2.start(); 
     for(;;) {
         qDebug() << "main()";
         QThread::sleep(1);
     }
     return 0;
}
```

## 事件驱动方式

> Qt 的事件驱动方式，将需要在线程中处理的业务放在独立的模块（类）中，由主线程创建完该对象后，将其移交给指定的线程，且可以将多个类似的对象移交给同一个线程。

- 线程中尽量不要操作UI对象（从 QWidget 直接或间接派生的窗口对象）。
- 对于需要移动到子线程中处理的模块类，创建对象的时候不能指定基类对象。

创建一个基类为 QMainWindow 的项目 EventThread，并添加一个基于基类 QObject 的新类 workmodule

`workmodule.h`

```cpp
private slots:
       void onTimeout();
```

`workmodule.cpp`

```cpp
void workmodule::onTimeout() {//线程执行的函数
     qDebug() << "当前线程:"<< QThread::currentThread();
     int sum = 0;
     for(int i = 1; i <= 1000000; i++){//求和计算，耗时操作
            sum =+ i;
     }
     qDebug() << "处理完成";
}
```

`main.cpp`

```cpp
int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     qDebug()<<"当前线程 "<<QThread::currentThreadId();
     QThread t;//Qt中的线程类，这里用作子线程
     QTimer timer;//用定时器自动触发事件
     workmodule worker;//工作的类
     //将定时器的timeout()信号与worker对象的槽函数相连
     QObject::connect(&timer, SIGNAL(timeout()),
                      &worker, SLOT(onTimeout()));
     //  将worker对象移交给线程t，通过定时器定时触发worker对象的槽函数
     worker.moveToThread(&t);
     // 启动定时器
     timer.start(1000);
     // 启动线程
     t.start();
     return app.exec();
}
```

## 线程退出

- quit()：Qt 中以事件循环的方式来管理窗口的运行，子线程也通过事件循环的方式来运行。调用 quit() 函数相当于告诉线程的事件循环以 “return 0” 成功退出，相当于调用 QThread::exit(0)。而一旦没有了事件循环，线程将不会继续运行，并等待回收。如果线程没有事件循环，这个函数什么也不做。但如果线程正在执行事件的处理函数，则会等待处理完毕。
- exit()：与 quit() 类似。
- terminate()：强行终止线程的运行，如果线程正在休眠中，通常会报告运行错误。