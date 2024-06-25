# Qt 事件

> Qt 应用程序是基于事件驱动的，在 main() 函数中创建一个 QApplication 对象，并调用它的 exec() 函数，这个函数就是开始 Qt 事件循环的函数。通常 Windows 操作系统会把从操作系统得到的消息，如鼠标移动、按键等放入操作系统的消息队列中，Qt 事件循环会不停地读取这些事件并依次处理。Qt 中的所有事件类都继承于类 QEvent。在事件对象创建完毕后，Qt 将这个事件对象传递给 QObject 的 event() 函数。event() 函数并不直接处理事件，而是按照事件对象的类型将其分派给特定的事件处理函数（event handler）

## 事件接收和忽略

Qt 中，所有控件都继承于类 QWidget，形成一种层次叠加的结构。在自定义控件的时候，派生类会继承基类的事件，但一般处理事件后，不会将事件继续传递给基类处理。可以把 Qt 的事件传递看成链式：如果派生类没有处理这个事件，就会继续向基类传递。

## 事件过滤器

Qt 提供了一种事件过滤的机制。Qt 在接收到消息并创建 QEvent 事件之后，会调用 event() 函数进行分发，而 event() 函数继承自QObject类，QObject 类中有一个 eventFilter() 函数，用于创建事件过滤器：

```cpp
virtual bool QObject::eventFilter(QObject * watched, QEvent* event);
```

eventFilter() 函数返回一个 bool 类型的值，如果想将函数 event() 过滤出来，如不想让它继续转发，就返回 true，否则返回 false。事件过滤器的调用在目标对象（也就是参数里面的watched对象）接收到事件对象之前。也就是说，如果在事件过滤器中停止了某个事件，那么 watched 对象和以后所有的事件过滤器都不会知道有这么一个事件。