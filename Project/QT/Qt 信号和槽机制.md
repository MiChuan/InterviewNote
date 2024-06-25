# Qt 信号和槽机制

## 信号和槽机制

Qt 提供了一种新的对象间的通信方式，即信号和槽机制。

### 信号和槽的使用

槽的本质就是类的成员函数，其参数可以是任意类型，可以是虚函数，可以被重载。槽通常和信号连接在一起，当信号被发出时，与这个信号连接的槽函数就会被调用。

```cpp
connect(sender, SIGNAL(signal), receiver, SLOT(slot));
```

- sender：发出信号的对象的指针。
- signal：发送对象发出的信号。
- receiver：接收信号的包含槽函数的对象的指针。
- slot：接收对象在接收到信号之后所需要调用的槽函数。

信号和槽是多对多的关系，可以一个信号连接多个槽，也可以多个信号连接同一个槽。

```cpp
connect(sender, SIGNAL(signal), receiverA, SLOT(slotA));
connect(sender, SIGNAL(signal), receiverB, SLOT(slotB));

connect(senderA, SIGNAL(signalA), receiver, SLOT(slot));
connect(senderB, SIGNAL(signalB), receiver, SLOT(slot));
```

### Lambda表达式

C++11 中的 Lambda 表达式用于定义并创建匿名的函数对象。需在 .pro 文件中加入

```cpp
CONFIG+=C++11
```

Lambda表达式的语法:

```cpp
[函数对象参数] (操作符重载函数参数) <mutable / exception> -> 返回值 
{
    函数体
}
```

**函数对象参数**

- 空，没有使用任何函数对象参数。
- “=”，函数体内可以使用 Lambda 表达式所在作用范围内所有可见的局部变量（包括 Lambda 表达式所在类的this），并且是值传递方式（相当于编译器自动按值传递了所有局部变量）。
- “&”，函数体内可以使用 Lambda 表达式所在作用范围内所有可见的局部变量（包括 Lambda 表达式所在类的this），并且是引用传递方式（相当于编译器自动按引用传递了所有局部变量）。

**操作符重载函数参数**

“()” 标识重载的操作符的参数，没有参数时，这部分可以省略。参数可以通过按值如 (a,b) 和按引用如 (&a,&b) 两种方式进行传递。

**可修改标识符和错误抛出标识符** ：mutable / exception

**函数返回值**

“->” 标识函数返回值的类型。当返回值为 void，或者函数体中只有一处返回的地方（此时编译器可以自动推断出返回值类型）时，这部分可以省略。

**函数体**

“{}” 标识函数的实现，这部分不能省略，但函数体可以为空。

**举个栗子**

`button.h`

```cpp
#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class button;
}

class button : public QWidget
{
    Q_OBJECT

public:
    explicit button(QWidget *parent = 0);
    ~button();

private:
    Ui::button *ui;
    QPushButton *button1;
};

#endif // BUTTON_H
```

`button.cpp`

```cpp
#include "button.h"
#include "ui_button.h"

button::button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::button)
{
    button1 = new QPushButton(this);
    button1->setParent(this);
    button1->setText("Lambda");
    connect(button1, &QPushButton::released,
            [=]()
            {
                button1->setText("hello");
            });
}

button::~button()
{
    delete ui;
}
```

