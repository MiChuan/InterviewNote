# C++

## 基础知识

### static关键字有什么作用？

> 声明有静态存储期和内部链接的命名空间成员
> 定义有静态存储期且仅初始化一次的块作用域变量
> 声明不绑定到特定实例的类成员

持久化、隐藏和默认初始化为0

- 修饰**局部变量**时，使得该变量在静态存储区分配内存；只能在首次函数调用中进行首次初始化，之后的函数调用不再进行初始化；其生命周期与程序相同，但其作用域为局部作用域，并不能一直被访问；

- 修饰**全局变量**时，使得该变量在静态存储区分配内存；在声明该变量的整个文件中都是可见的，而在文件外是不可见的；

- 修饰**函数**时，在声明该函数的整个文件中都是可见的，而在文件外是不可见的，从而可以在多人协作时避免同名的函数冲突；

- 修饰**成员变量**

  - 静态数据成员不关联到任何对象。即使不定义类的任何对象它们也存在。整个程序中只有一个拥有静态存储期的静态数据成员实例，除非使用关键词 thread_local ，该情况下每个线程都有一个拥有线程存储期的该对象 (C++11 起)。
  - 静态数据成员不能为 mutable 。
  - 在命名空间作用域中，若类自身拥有外部链接（即不是无名命名空间的成员），则类的静态数据成员拥有外部链接。局部类（定义于函数内部的类）和无名类，含无名类的成员类，不能拥有静态数据成员。
  - 不需要实例化对象即可访问；类体内的声明不是定义，且可以声明拥有不完整类型（异于 void）的成员，包含该成员的声明所在的类型：

  ```cpp
  struct Foo;
  struct S
  {
     static int a[];  // 声明，不完整类型
     static Foo x;    // 声明，不完整类型
     static S s;      // 声明，不完整类型（在其自身定义中）
  };
   
  int S::a[10];       // 定义，完整类型
  struct Foo {};
  Foo S::x;           // 定义，完整类型
  S S::s;             // 定义，完整类型
  ```

- 修饰**成员函数**

  - 静态成员函数不关联到任何对象。调用时，它们无 this 指针
  - 静态成员函数不能为 virtual 、 const 或 volatile
  - 静态成员函数的地址可以存储在常规的指向函数指针中，但不能存储于指向成员函数指针中


### 指针和引用的区别？

- 指针是一个变量，存储的是一个地址，引用跟原来的变量实质上是同一个东西，是原变量的别名

- 指针可以有多级，引用只有一级

- 指针可以为空，引用不能为NULL且在定义时必须初始化

- 指针在初始化后可以改变指向，而引用在初始化之后不可再改变

- sizeof指针得到的是本指针的大小，sizeof引用得到的是引用所指向变量的大小

- 引用不是对象；它们不必占用存储，尽管若需要分配存储以实现所需语义（例如，引用类型的非静态数据成员通常会增加类的大小，量为存储内存地址所需），则编译器会这么做。

- 无到 void 的引用，无引用的数组，无指向引用的指针，无到引用的引用：

  ```cpp
  int& void func(){} // 错误
  int& a[3];         // 错误
  int&* p;           // 错误
  int& &r;           // 错误
  ```

### #define和const有什么区别？

- 编译器处理方式不同：#define宏是在预处理阶段展开，不能对宏定义进行调试，而const常量是在编译阶段使用；
- 类型和安全检查不同：#define宏没有类型，不做任何类型检查，仅仅是代码展开，而const常量有具体类型，在编译阶段会执行类型检查；
- 存储方式不同：#define宏仅仅是代码展开，在多个地方进行字符串替换，不会分配内存，存储于程序的代码段中，而const常量会分配内存，但只维持一份拷贝，存储于程序的数据段中。
- 定义域不同：#define宏不受定义域限制，而const常量只在定义域内有效。

### typedef 和#define 有什么区别？

- 用法不同：typedef 用来定义一种数据类型的别名，增强程序的可读性。define 主要用来定义 常量，以及书写复杂使用频繁的宏。
- 执行时间不同：typedef 是编译过程的一部分，有类型检查的功能。define 是宏定义，是预编译的部分，其发生在编译之前，只是简单的进行字符串的替换，不进行类型的检查。
- 作用域不同：typedef 有作用域限定。define 不受作用域约束，只要是在define 声明后的引用 都是正确的。
- 对指针的操作不同：typedef 和define 定义的指针时有很大的区别。

### 静态链接和动态链接有什么区别？

- 静态链接是在编译链接时直接将需要的执行代码拷贝到调用处；

  优点在于程序在发布时不需要依赖库，可以独立执行，缺点在于程序的体积会相对较大，而且如果静态库更新之后，所有可执行文件需要重新链接；

- 动态链接是在编译时不直接拷贝执行代码，而是通过记录一系列符号和参数，在程序运行或加载时将这些信息传递给操作系统，操作系统负责将需要的动态库加载到内存中，然后程序在运行到指定代码时，在共享执行内存中寻找已经加载的动态库可执行代码，实现运行时链接；优点在于多个程序可以共享同一个动态库，节省资源；缺点在于由于运行时加载，可能影响程序的前期执行性能。

### struct和class的区别?

**相同点**

- 两者都拥有成员函数、公有和私有部分
- 任何可以使用class完成的工作，同样可以使用struct完成

**不同点**

- 两者中如果不对成员不指定公私有，struct默认是公有的，class则默认是私有的
- class默认是private继承，而struct模式是public继承

### 结构体内存对齐问题？

- 结构体内成员按照声明顺序存储，第一个成员地址和整个结构体地址相同。
- 未特殊说明时，按结构体中size最大的成员对齐（若有double成员，按8字节对齐。）
- c++11以后引入两个关键字 `alignas`与 `alignof`。其中`alignof`可以计算出类型的对齐方式，`alignas`可以指定结构体的对齐方式。

### new / delete 与 malloc / free的异同？

**相同点**

- 都可用于内存的动态申请和释放

**不同点**

- 前者是C++运算符，后者是C/C++语言标准库函数
- new自动计算要分配的空间大小，malloc需要手工计算
- new是类型安全的，malloc不是。例如：

```cpp
int *p = new float[2]; //编译错误
int *p = (int*)malloc(2 * sizeof(double));//编译无错误
```

- new调用名为**operator new**的标准库函数分配足够空间并调用相关对象的构造函数，delete对指针所指对象运行适当的析构函数；然后通过调用名为**operator delete**的标准库函数释放该对象所用内存。后者均没有相关调用
- 后者需要库文件支持，前者不用
- new是封装的malloc，直接free不会报错，但是这只是释放内存，而不会析构对象

[operator new与operator delete](https://juejin.cn/post/7084416011339825183)

### delete与delete []有什么区别？

- 对于简单类型来说，使用new分配后，不管是数组数组还是非数组形式，两种方式都可以释放内存：

  ```cpp
  int *a = new int(1);
  delete a;
  int *b = new int(2);
  delete [] b;
  int *c = new int[11];
  delete c;
  int *d = new int[12];
  delete [] d;
  ```

- 对于自定义类型来说，就需要对于单个对象使用delete，对于对象数组使用delete []，逐个调用数组中对象的析构函数，从而释放所有内存；如果反过来使用，即对于单个对象使用delete []，对于对象数组使用delete，其行为是未定义的；

- 所以，最恰当的方式就是如果用了new，就用delete；如果用了new []，就用delete []。

### 简述#ifdef、#else、#endif和#ifndef的作用

- 启用/屏蔽某个模块
- 调试开关
- 应对编译环境的变化
- 保护头文件，避免多次包含同一头文件

### sizeof 和strlen 的区别

- sizeof是一个操作符，strlen是库函数。
- sizeof的参数可以是数据的类型，也可以是变量，而strlen只能以结尾为‘\0’的字符串作参数。
- 编译器在编译时就计算出了sizeof的结果，而strlen函数必须在运行时才能计算出来。并且sizeof计算的是数据类型占内存的大小，而strlen计算的是字符串实际的长度。

### 简述strcpy、sprintf 与memcpy 的区别

- 操作对象不同，strcpy 的两个操作对象均为字符串，sprintf 的操作源对象可以是多种数据类型， 目的操作对象是字符串，memcpy 的两个对象就是两个任意可操作的内存地址，并不限于何种数据类型。
- 执行效率不同，memcpy 最高，strcpy 次之，sprintf 的效率最低。
- 实现功能不同，strcpy 主要实现字符串变量间的拷贝，sprintf 主要实现其他数据类型格式到字 符串的转化，memcpy 主要是内存块间的拷贝。

### 对于一个频繁使用的短小函数，应该使用什么来实现？有什么优缺点？

应该使用inline内联函数，即编译器将inline内联函数内的代码替换到函数被调用的地方。

优点：

- 在内联函数被调用的地方进行代码展开，省去函数调用的时间，从而提高程序运行效率；
- 相比于宏函数，内联函数在代码展开时，编译器会进行语法安全检查或数据类型转换，使用更加安全；

缺点：

- 代码膨胀，产生更多的开销；
- 如果内联函数内代码块的执行时间比调用时间长得多，那么效率的提升并没有那么大；
- 如果修改内联函数，那么所有调用该函数的代码文件都需要重新编译；
- 内联声明只是建议，是否内联由编译器决定，所以实际并不可控。

### RAII

> 资源获取即初始化（ Resource Acquisition Is Initialization ），或称 RAII ，是一种 C++ 编程技术，它将必须在使用前请求的资源（被分配的堆内存、执行的线程、打开的套接字、打开的文件、被锁的互斥、磁盘空间、数据库连接等——任何存在于受限供给中的事物）的生命周期绑定到一个对象的生存期。

> RAII 保证资源可用于任何会访问该对象的函数（资源可用性是一种类不变量，这会消除冗余的运行时测试）。它亦保证所有资源的在其控制对象的生存期结束时被释放，以获取顺序的逆序。类似地，若资源获取失败（构造函数以异常退出），则所有已为完全构造的对象和基类子对象所获取的资源，会被以初始化顺序的逆序释放。这会有效利用语言特性（对象生存期、退出作用域、初始化顺序以及栈回溯）以消除内存泄漏并保证异常安全。此技术的另一名称是作用域界定的资源管理（ Scope-Bound Resource Management ， SBRM ），根据 RAII 对象的生存期在退出作用域时结束这一基本状况。

RAII 可总结如下:

- 将每个资源封装入一个类
  - 构造函数请求资源，并建立所有类不变量或在它无法完成时抛出异常，
  - 析构函数释放资源并决不抛出异常；
- 始终经由 RAII 类的实例使用满足要求的资源
  - 该资源自身拥有自动存储期或临时生存期
  - 或拥有绑定于自动或临时对象的生存期

移动语义令在维护资源安全的同时，在对象间、跨作用域，以及线程内外移动安全移动所有权成为可能。

拥有 open()/close() 、 lock()/unlock() ，或 init()/copyFrom()/destroy() 成员函数的类是非 RAII 类的典型的🌰：

```cpp
std::mutex m;
 
void bad() 
{
    m.lock();                    // 请求互斥
    f();                         // 若 f() 抛异常，则互斥决不被释放
    if(!everything_ok()) return; // 提早返回，互斥决不被释放
    m.unlock();                  // 若 bad() 抵达此语句，互斥才被释放
}
 
void good()
{
    std::lock_guard<std::mutex> lk(m); // RAII类：互斥请求即是初始化
    f();                               // 若f()抛异常，则释放互斥
    if(!everything_ok()) return;       // 提早返回，互斥被释放
}       
```

### 什么是智能指针？智能指针有什么作用？分为哪几种？各自有什么样的特点？

智能指针是一个RAII类模型，用于动态分配内存，其设计思想是将基本类型指针封装为（模板）类对象指针，并在离开作用域时调用析构函数，使用delete删除指针所指向的内存空间。

智能指针的作用是，能够处理**内存泄漏**和**空悬指针**。

分为auto_ptr、unique_ptr、shared_ptr和weak_ptr四种，各自的特点：

- 对于auto_ptr，实现独占式拥有的概念，同一时间只能有一个智能指针可以指向该对象；但auto_ptr

  在C++11中被摒弃，其主要问题在于：

  - 对象所有权的转移，比如在函数传参过程中，对象所有权不会返还，从而存在潜在的内存崩溃问题；
  - 不能指向数组，也不能作为STL容器的成员。

- 对于unique_ptr，实现独占式拥有的概念，同一时间只能有一个智能指针可以指向该对象，因为无法进行**拷贝构造**和**拷贝赋值**，但是可以进行**移动构造**和**移动赋值**；

- 对于shared_ptr，实现共享式拥有的概念，即多个智能指针可以指向相同的对象，该对象及相关资源会在其所指对象不再使用之后，自动释放与对象相关的资源；

- 对于weak_ptr，解决shared_ptr相互引用时，两个指针的引用计数永远不会下降为0，从而导致死锁问题。而weak_ptr是对对象的一种弱引用，可以绑定到shared_ptr，但不会增加对象的引用计数。

### 右值引用有什么作用？

右值引用的主要目的是为了实现转移语义和完美转发，消除两个对象交互时不必要的对象拷贝，也能够更加简洁明确地定义泛型函数

[一次性搞定右值，右值引用（&&），和move语义](https://juejin.cn/post/6844903497075294216)

### 在main执行之前和之后执行的代码可能是什么？

**main函数执行之前**，主要就是初始化系统相关资源：

- 设置栈指针
- 初始化静态`static`变量和`global`全局变量，即`.data`段的内容
- 将未初始化部分的全局变量赋初值：数值型`short`，`int`，`long`等为`0`，`bool`为`FALSE`，指针为`NULL`等等，即`.bss`段的内容
- 全局对象初始化，在`main`之前调用构造函数，这是可能会执行前的一些代码
- 将main函数的参数`argc`，`argv`等传递给`main`函数，然后才真正运行`main`函数
- `__attribute__((constructor))`

**main函数执行之后**：

- 全局对象的析构函数会在main函数之后执行；
- 可以用 **`atexit`** 注册一个函数，它会在main 之后执行;
- `__attribute__((destructor))`

### 堆和栈的区别

- 申请方式不同。
  - 栈由系统自动分配。
  - 堆是程序员申请和释放的。
- 申请大小限制不同。
  - 栈顶和栈底是之前预设好的，栈是向栈底扩展，大小固定，可以通过ulimit -a查看，由ulimit -s修改。
  - 堆向高地址扩展，是不连续的内存区域，大小可以灵活调整。
- 申请效率不同。
  - 栈由系统分配，速度快，不会有碎片。
  - 堆由程序员分配，速度慢，且会有碎片。

### final和override关键字

**override**

当在父类中使用了虚函数时候，你可能需要在某个子类中对这个虚函数进行重写，以下方法都可以：

```cpp
class A
{
    virtual void foo();
}
class B : public A
{
    void foo(); //OK
    virtual void foo(); // OK
    void foo() override; //OK
}
```

如果不使用override，当你手一抖，将**foo()**写成了**f00()**会怎么样呢？结果是编译器并不会报错，因为它并不知道你的目的是重写虚函数，而是把它当成了新的函数。如果这个虚函数很重要的话，那就会对整个程序不利。所以，override的作用就出来了，它指定了子类的这个虚函数是重写的父类的，如果你名字不小心打错了的话，编译器是不会编译通过的：

```cpp
class A
{
    virtual void foo();
};
class B : public A
{
    virtual void f00(); //OK，这个函数是B新增的，不是继承的
    virtual void f0o() override; //Error, 加了override之后，这个函数一定是继承自A的，A找不到就报错
};
```

**final**

当不希望某个类被继承，或不希望某个虚函数被重写，可以在类名和虚函数后添加final关键字，添加final关键字后被继承或重写，编译器会报错。🌰如下：

```cpp
class Base
{
    virtual void foo();
};

class A : public Base
{
    void foo() final; // foo 被override并且是最后一个override，在其子类中不可以重写
};

class B final : A // 指明B是不可以被继承的
{
    void foo() override; // Error: 在A中已经被final了
};

class C : B // Error: B is final
{
};
```

### C++中的重载、重写（覆盖）和隐藏的区别

**重载**（overload）

重载是指在同一个类中定义中的同名成员函数才存在重载关系。主要特点是**函数名相同，参数类型和数目有所不同**，不能出现参数个数和类型均相同，仅仅依靠返回值不同来区分的函数。重载和函数成员是否是虚函数无关。举个🌰：

```cpp
class A{
    ...
    virtual int fun();
    void fun(int);
    void fun(double, double);
    static int fun(char);
    ...
}
```

（2）重写（覆盖）（override）

重写指的是在派生类中覆盖基类中的同名函数，**重写就是重写函数体**，**要求基类函数必须是虚函数**且：

- 与基类的虚函数有相同的**参数个数**
- 与基类的虚函数有相同的**参数类型**
- 与基类的虚函数有相同的**返回值类型**

举个🌰：

```cpp
//父类
class A{
public:
    virtual int fun(int a){}
}
//子类
class B : public A{
public:
    //重写,一般加override可以确保是重写父类的函数
    virtual int fun(int a) override{}
}
```

重载与重写的区别：

- 重写是**父类**和**子类**成员函数之间的垂直关系；重载是一个类中不同**成员函数**之间的水平关系
- 重写要求**参数**列表和**返回值**相同；重载则要求**参数列表不同**，返回值不要求
- 重写关系中，调用方法根据**对象类型**决定；重载根据调用时**实参表**与**形参表**的对应关系来选择函数体

（3）隐藏（hide）

隐藏指的是某些情况下，派生类中的函数屏蔽了基类中的同名函数，包括以下情况：

- 两个函数参数相同，但是基类函数不是虚函数。**和重写的区别在于基类函数是否是虚函数。**举个🌰：

```cpp
//父类
class A{
public:
    void fun(int a){
        cout << "A中的fun函数" << endl;
    }
};
//子类
class B : public A{
public:
    //隐藏父类的fun函数
    void fun(int a){
        cout << "B中的fun函数" << endl;
    }
};
int main(){
    B b;
    b.fun(2); //调用的是B中的fun函数
    b.A::fun(2); //调用A中fun函数
    return 0;
}
```

- **两个函数参数不同，无论基类函数是不是虚函数，都会被隐藏。和重载的区别在于两个函数不在同一个类中。举个🌰：**

```cpp
//父类
class A{
public:
    virtual void fun(int a){
        cout << "A中的fun函数" << endl;
    }
};
//子类
class B : public A{
public:
    //隐藏父类的fun函数
   virtual void fun(char* a){
       cout << "A中的fun函数" << endl;
   }
};
int main(){
    B b;
    b.fun(2); //报错，调用的是B中的fun函数，参数类型不对
    b.A::fun(2); //调用A中fun函数
    return 0;
}
```

补充：

```c++
// 父类
class A {
public:
    virtual void fun(int a) { // 虚函数
        cout << "This is A fun " << a << endl;
    }  
    void add(int a, int b) {
        cout << "This is A add " << a + b << endl;
    }
};

// 子类
class B: public A {
public:
    void fun(int a) override {  // 覆盖
        cout << "this is B fun " << a << endl;
    }
    void add(int a) {   // 隐藏
        cout << "This is B add " << a + a << endl;
    }
};

int main() {
    // 基类指针指向派生类对象时，基类指针可以直接调用到派生类的覆盖函数，也可以通过 :: 调用到基类被覆盖
    // 的虚函数；而基类指针只能调用基类的被隐藏函数，无法识别派生类中的隐藏函数。

    A *p = new B();
    p->fun(1);      // 调用子类 fun 覆盖函数
    p->A::fun(1);   // 调用父类 fun
    p->add(1, 2);
    // p->add(1);      // 错误，识别的是 A 类中的 add 函数，参数不匹配
    // p->B::add(1);   // 错误，无法识别子类 add 函数
    return 0;
}
```

### 浅拷贝和深拷贝的区别

**浅拷贝**

浅拷贝只是**拷贝一个指针**，并没有新开辟一个地址，拷贝的指针和原来的指针指向**同一块地址**，如果原来的指针所指向的资源释放了，那么再释放浅拷贝的指针的资源就会出现错误。

**深拷贝**

深拷贝开辟出一块**新的空间**用来存放拷贝的值，即使原先的对象被析构掉，释放内存了也不会影响到深拷贝得到的值。在自己实现拷贝赋值的时候，如果有指针变量的话是需要自己实现深拷贝的。

```cpp
#include <iostream>  
#include <string.h>
using namespace std;

class Student
{
private:
    int num;
    char *name;
public:
    Student(){
        name = new char(20);
        cout << "Student" << endl;
    };
    ~Student(){
        cout << "~Student " << &name << endl;
        delete name;
        name = NULL;
    };
    Student(const Student &s){//拷贝构造函数
        //浅拷贝，当对象的name和传入对象的name指向相同的地址
        name = s.name;
        //深拷贝
        //name = new char(20);
        //memcpy(name, s.name, strlen(s.name));
        cout << "copy Student" << endl;
    };
};

int main()
{
    {// 花括号让s1和s2变成局部对象，方便测试
        Student s1;
        Student s2(s1);// 复制对象
    }
    system("pause");
    return 0;
}
//浅拷贝执行结果：
//Student
//copy Student
//~Student 0x7fffed0c3ec0
//~Student 0x7fffed0c3ed0
//*** Error in `/tmp/815453382/a.out': double free or corruption (fasttop): 0x0000000001c82c20 ***

//深拷贝执行结果：
//Student
//copy Student
//~Student 0x7fffebca9fb0
//~Student 0x7fffebca9fc0
```

### 如何用代码判断大小端存储？

[轻松记住大端小端的含义](https://www.cnblogs.com/wuyuegb2312/archive/2013/06/08/3126510.html)

大小端与CPU有关，与编译器和操作系统类型无关；x86、arm是小端，MAC是大端，MIPS可以配置；TCP/IP协议、Java虚拟机规定为大端模式。

> MSB（Most Significant Bit/Byte）通常用来表明在一个bit序列（如一个byte是8个bit组成的一个序列） 或一个byte序列（如word是两个byte组成的一个序列）中对整个序列取值影响最大的那个bit/byte。LSB（Least Significant Bit/Byte）通常用来表明在一个bit序列（如一个byte是8个bit组成的一个序列） 或一个byte序列（如word是两个byte组成的一个序列） 中对整个序列取值影响最小的那个bit/byte。

- 大端存储（高尾端）：字数据的**MSB**存储在**低地址**中
- 小端存储（低尾端）：字数据的**MSB**存储在**高地址**中

举个🌰：`0x11223344`，`0x11`是MSB

| 地址 | 大端 | 小端 |
| ---- | ---- | ---- |
| 0x0  | 0x11 | 0x44 |
| 0x1  | 0x22 | 0x33 |
| 0x2  | 0x33 | 0x22 |
| 0x3  | 0x44 | 0x11 |

**方式一：使用强制类型转换**

```cpp
#include <iostream>
using namespace std;
int main()
{
    int a = 0x1234;
    //由于int和char的长度不同，借助int型转换成char型，只会留下低地址的部分
    char c = (char)(a);
    if (c == 0x12)
        cout << "big endian" << endl;
    else if(c == 0x34)
        cout << "little endian" << endl;
}
```

**方式二：巧用union联合体**

```cpp
#include <iostream>
using namespace std;
//union联合体的重叠式存储，endian联合体占用内存的空间为每个成员字节长度的最大值
union endian
{
    int a;
    char ch;
};
int main()
{
    endian value;
    value.a = 0x1234;
    //a和ch共用4字节的内存空间
    if (value.ch == 0x12)
        cout << "big endian"<<endl;
    else if (value.ch == 0x34)
        cout << "little endian"<<endl;
}
```

### volatile、mutable和explicit关键字的用法

> const 定义类型为常。
> volatile 义类型为易变。
> mutable 应用于非引用非 const 类型的非静态类成员，并指定该成员不影响类的外部可见状态。 const 类实例的 mutable 成员是可修改的。

**volatile**

volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。

当要求使用 volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据。

volatile定义变量的值是易变的，每次用到这个变量的值的时候都要去重新读取这个变量的值，而不是读寄存器内的备份。多线程中被几个任务共享的变量需要定义为volatile类型。

volatile 指针

volatile 指针和 const 修饰词类似，const 有常量指针和指针常量的说法，volatile 也有相应的概念

修饰由指针指向的对象、数据是 const 或 volatile 的：

```cpp
const char* cpch;
volatile char* vpch;
```

指针自身的值——一个代表地址的整数变量，是 const 或 volatile 的：

```cpp
char* const pchc;
char* volatile pchv;
```

注意：

- 可以把一个非volatile int赋给volatile int，但是不能把非volatile对象赋给一个volatile对象。
- 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。
- C++中一个有volatile标识符的类只能访问它接口的子集，一个由类的实现者控制的子集。用户只能用const_cast来获得对类型接口的完全访问。此外，volatile向const一样会从类传递到它的成员。

多线程下的volatile

有些变量是用volatile关键字声明的。当两个线程都要用到某一个变量且该变量的值会被改变时，应该用volatile声明，该关键字的作用是防止优化编译器把变量从内存装入CPU寄存器中。如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，这会造成程序的错误执行。volatile的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值。

**mutable**

mutable的中文意思是“可变的，易变的”，跟constant（既C++中的const）是反义词。在C++中，mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。我们知道，如果类的成员函数不会改变对象的状态，那么这个成员函数一般会声明成const的。但是，有些时候，我们需要在const函数里面修改一些跟类状态无关的数据成员，那么这个函数就应该被mutable来修饰，并且放在函数后后面关键字位置。

```CPP
class personA {
private:
    int m_A;
    mutable int m_B;  //特殊变量 在常函数里值也可以被修改
public:
    //在函数里不可修改this指针指向的值 常量指针
    void add() const{
        m_A=10;  //错误  不可修改值，this已经被修饰为常量指针
        m_B=20;  //正确
    }
}
class personB {
private:
    int m_A;
    mutable int m_B;  //特殊变量 在常函数里值也可以被修改
}
int main() {
    const personB p;    //修饰常对象 不可修改类成员的值
    p.m_A = 10;         //错误，被修饰了指针常量
    p.m_B = 200;        //正确，特殊变量，修饰了mutable
}
```

**explicit**

explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换，只能以显示的方式进行类型转换，注意以下几点：

- explicit 关键字只能用于类内部的构造函数声明上
- explicit 关键字作用于单个参数的构造函数
- 被explicit修饰的构造函数的类，不能发生相应的隐式类型转换

### C++的异常处理的方法

- **try、throw和catch关键字**

- **函数的异常声明列表**

有时候，程序员在定义函数的时候知道函数可能发生的异常，可以在函数声明和定义时，指出所能抛出异常的列表，写法如下：

```cpp
int fun() throw(int, double, A, B, C) {...};
```

这种写法表名函数可能会抛出int,double型或者A、B、C三种类型的异常，如果throw中为空，表明不会抛出任何异常，如果没有throw则可能抛出任何异常

- **C++标准异常类 exception**

C++ 标准库中有一些类代表异常，这些类都是从 exception 类派生而来的，如下图所示

![img](https://cdn.jsdelivr.net/gh/forthespada/mediaImage2@2.6/202104/C++-49-1.png)

- bad_typeid：使用typeid运算符，如果其操作数是一个多态类的指针，而该指针的值为 NULL，则会拋出此异常

- bad_cast：在用 dynamic_cast 进行从多态基类对象（或引用）到派生类的引用的强制类型转换时，如果转换是不安全的，则会拋出此异常
- bad_alloc：在用 new 运算符进行动态内存分配时，如果没有足够的内存，则会引发此异常
- out_of_range:用 vector 或 string的at成员函数根据下标访问元素时，如果下标越界，则会拋出此异常

### malloc、realloc、calloc的区别

1) malloc函数

```cpp
void* malloc(unsigned int num_size);
int *p = malloc(20 * sizeof(int));  //申请20个int类型的空间；
```

2) calloc函数

```cpp
void* calloc(size_t n, size_t size);
int *p = calloc(20, sizeof(int));
```

省去了人为空间计算；malloc申请的空间的值是随机初始化的，calloc申请的空间的值是初始化为0的；

3) realloc函数

```cpp
void realloc(void *p, size_t new_size);
```

给动态分配的空间分配额外的空间，用于扩充容量。

### C++中新增了string，它与C语言中的 char *有什么区别吗？它是如何实现的？

**类模板定义**

```cpp
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>
> class basic_string;
```

| 类型                       | 定义                        |
| -------------------------- | --------------------------- |
| **std::string**            | std::basic_string<char>     |
| **std::wstring**           | std::basic_string<wchar_t>  |
| **std::u16string** (C++11) | std::basic_string<char16_t> |
| **std::u32string** (C++11) | std::basic_string<char32_t> |

**模板形参**

| 参数名    | 解释                                       |
| --------- | ------------------------------------------ |
| CharT     | 字符类型                                   |
| Traits    | 指定字符类型上操作的特性类                 |
| Allocator | 用于分配内部存储的分配器(*Allocator*) 类型 |

**不同点**

- string继承自basic_string，其实是对char* 进行了封装，封装的string包含了char* 数组，容量，长度等等属性。
- string可以进行动态扩展，在每次扩展的时候另外申请一块原空间大小两倍的空间（2^n），然后将原字符串拷贝过去，并加上新增的内容。

### 介绍面向对象的三大特性，并且举例说明

三大特性：继承、封装和多态

**（1）继承**

**让某种类型对象获得另一个类型对象的属性和方法。**

它可以使用现有类的所有功能，并在无需重新编写原来的类的情况下对这些功能进行扩展

常见的继承有三种方式：

1. 实现继承：指使用基类的属性和方法而无需额外编码的能力
2. 接口继承：指仅使用属性和方法的名称、但是子类必须提供实现的能力
3. 可视继承：指子窗体（类）使用基窗体（类）的外观和实现代码的能力（QT）

例如，将人定义为一个抽象类，拥有姓名、性别、年龄等公共属性，吃饭、睡觉、走路等公共方法，在定义一个具体的人时，就可以继承这个抽象类，既保留了公共属性和方法，也可以在此基础上扩展跳舞、唱歌等特有方法

**（2）封装**

数据和代码捆绑在一起，避免外界干扰和不确定性访问。

封装，也就是**把客观事物封装成抽象的类**，并且类可以把自己的数据和方法只让可信的类或者对象操作，对不可信的进行信息隐藏，例如：将公共的数据或方法使用public修饰，而不希望被访问的数据或方法采用private修饰。

**（3）多态**

同一事物表现出不同事物的能力，即向不同对象发送同一消息，不同的对象在接收时会产生不同的行为**（重载实现编译时多态，虚函数实现运行时多态）**。

多态性是允许你将父对象设置成为和一个或更多的他的子对象相等的技术，赋值之后，父对象就可以根据当前赋值给它的子对象的特性以不同的方式运作。**简单一句话：允许将子类类型的指针赋值给父类类型的指针**

实现多态有二种方式：覆盖（override），重载（overload）。

- 覆盖：是指子类重新定义父类的虚函数的做法。

- 重载：是指允许存在多个同名函数，而这些函数的参数表不同（或许参数个数不同，或许参数类型不同，或许两者都不同）。

### C++的四种强制转换

[C++ RTTI 和四种类型转换](https://juejin.cn/post/6934965352539357191)

### 结构体变量比较是否相等

1) 重载了 “==” 操作符

```cpp
struct foo {
  int a;
  int b;
  bool operator==(const foo& rhs) { //操作运算符重载
    return (a == rhs.a) && (b == rhs.b);
  }
};
```

2) 成员变量一个个比较；

3) 指针直接比较，如果保存的是同一个实例地址，则(p1 == p2)为真；

### 友元函数和友元类

[C++友元 ](https://juejin.cn/post/7052948579886825479)

1. 指明一个或数个函数为此类的友元 

   ```cpp
   class Y {
       int data; // 私有成员
       // std空间非类成员运算符 operator<< 将拥有对 Y 的私有成员的访问
       friend std::ostream& operator<<(std::ostream& out, const Y& y);
       friend char* X::foo(int);   // 其他类的成员亦可为友元
       friend X::X(char), X::~X(); // 构造函数与析构函数亦可为友元
   };
   // 友元声明不声明成员函数
   // 此 operator<< 仍需定义，作为非成员
   std::ostream& operator<<(std::ostream& out, const Y& y)
   {
       return out << y.data; // 能访问私有成员 Y::data
   }
   ```

2. 定义一个非成员函数，同时令之为此类的友元。这种非成员函数始终为 inline 。

❗❗❗**注意**

- 友元关系不传递
- 友元关系不继承
- 友元函数声明中不允许存储类指定符。以友元声明定义的函数拥有外部链接，先前已定义的函数保持其定义所有的链接
- 局部类声明一个非限定函数或类为友元时，只查找在最内层非类作用域的函数与类，而非全局函数

## C++11

### nullptr替代 NULL

- 关键词`nullptr`指代指针字面量。它是 std::nullptr_t 类型的纯右值。存在从 nullptr 到任何指针类型及任何指向成员指针类型的隐式转换。
- 宏`NULL`是实现定义的空指针常量，可为零值整数字面量，或为 std::nullptr_t 类型纯右值
- C 中，宏 `NULL` 可以拥有类型 `void*` ，但这在 C++ 中不允许。

```cpp
#define NULL 0
//C++11后
#define NULL nullptr
```

[What exactly is nullptr?](https://stackoverflow.com/questions/1282295/what-exactly-is-nullptr)

### 引入 auto 和 decltype 实现类型推导

[C++ 中 auto 与 decltype 的用法与区别](https://juejin.cn/post/6963517711137636360)

[C++11 通过 auto 与 decltype 来解决返回值难以推断的问题](https://juejin.cn/post/7029062602940481567)

### 基于范围的 for 循环

### 类和结构体的初始化列表

### Lambda 表达式

### 右值引用和move语义

[一次性搞定右值，右值引用（&&），和move语义](https://juejin.cn/post/6844903497075294216)

### 智能指针

[c++11新特性之智能指针](https://juejin.cn/post/6844904146844254215)

## 内存管理

### 类的对象存储空间大小？

- 非静态成员的数据类型大小之和
- 虚函数指针
- 内存对齐的padding
- 空类大小1字节

```cpp
#include <iostream>
using namespace std;

class A
{
    static int a;  
};
class B
{

};
class C
{
    virtual int a() = 0;
    virtual double b() = 0;
};
class D
{
    int a(){}
};

int main()
{
    A a;
    cout << sizeof(A) << endl;
    cout << sizeof(a) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    cout << sizeof(D) << endl;
    return 0;
}

/*
运行结果：
1
1
1
8
1
*/
```

[C++ 类内存分布](https://juejin.cn/post/6844903457447477262)

### C++的内存分区

[C/C++内存分布及管理方式](https://juejin.cn/post/7083624206239268872)

C++中的内存分区，分别是堆、栈、自由存储区、全局/静态存储区、常量存储区和代码区。如下图所示

![img](https://cdn.jsdelivr.net/gh/forthespada/mediaImage2@2.6/202104/C++-48-1.png)

**栈**：在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限

**堆**：就是那些由 `new`分配的内存块，他们的释放编译器不去管，由我们的应用程序去控制，一般一个`new`就要对应一个 `delete`。如果程序员没有释放掉，那么在程序结束后，操作系统会自动回收

**自由存储区**：如果说堆是操作系统维护的一块内存，那么自由存储区就是C++中通过new和delete动态分配和释放对象的抽象概念。需要注意的是，自由存储区和堆比较像，但不等价。

**全局/静态存储区**：全局变量和静态变量被分配到同一块内存中，在以前的C语言中，全局变量和静态变量又分为初始化的和未初始化的，在C++里面没有这个区分了，它们共同占用同一块内存区，在该区定义的变量若没有初始化，则会被自动初始化，例如int型变量自动初始为0

**常量存储区**：这是一块比较特殊的存储区，这里面存放的是常量，不允许修改

**代码区**：存放函数体的二进制代码

### 什么是内存池，如何实现？

[C++ 内存池介绍与经典内存池的实现](https://blog.csdn.net/k346k346/article/details/49538975)

### this指针

[this指针](https://juejin.cn/post/7060301769988898847)

- this指针是类的指针，指向对象的首地址。
- this指针只能在成员函数中使用，在全局函数、静态成员函数中都不能用this。
- this 指针本质上其实是一个成员函数的形参，是对象调用成员函数时，将对象地址作为实参传递给 this 形参。所以对象中不存储 this 指针。
- this指针是成员函数第一个隐含的指针形参，一般情况由编译器通过ecx寄存器自动传递，不需要用户传递

**this指针的用处**

一个对象的this指针并不是对象本身的一部分，不会影响 sizeof(对象) 的结果。this作用域是在类内部，当在类的**非静态成员函数**中访问类的**非静态成员**的时候（全局函数，静态函数中不能使用this指针），编译器会自动将对象本身的地址作为一个隐含参数传递给函数。也就是说，即使你没有写上this指针，编译器在编译的时候也是加上this的，它作为非静态成员函数的隐含形参，对各成员的访问均通过this进行

**this指针的使用**

一种情况就是，在类的非静态成员函数中返回类对象本身的时候，直接使用 `return *this；`

另外一种情况是当形参数与成员变量名相同时用于区分，如`this->n = n` （不能写成n = n）

**类的this指针有以下特点**

(1）**this**只能在成员函数中使用，全局函数、静态函数都不能使用this。实际上，**传入参数为当前对象地址，成员函数第一个参数为**为**T \* const this**

如：

```C++
class A{
public:
    int func(int p){}
};
```

其中，**func**的原型在编译器看来应该是：

```cpp
int func(A* const this, int p);
```

（2）由此可见，this在成员函数的开始前构造，在成员函数的结束后清除。这个生命周期同任何一个函数的参数是一样的，没有任何区别。当调用一个类的成员函数时，编译器将类的指针作为函数的this参数传递进去。如：

```C++
A a;
a.func(10); //此处，编译器将会编译成：A::func(&a, 10);
```

看起来和静态函数没差别，对吗？不过，区别还是有的。编译器通常会对this指针做一些优化，因此，this指针的传递效率比较高，例如VC通常是通过ecx（计数寄存器）传递this参数的。

### 内存泄漏？

[内存泄漏](https://juejin.cn/post/7085491034091683870)

## 面向对象（**Object** Oriented Programming）

### C++的多态如何实现

[C++ 类内存分布](https://juejin.cn/post/6844903457447477262)

>虚表：虚函数表的缩写，类中含有virtual关键字修饰的方法时，编译器会自动生成虚表
>
>虚表指针：在含有虚函数的类实例化对象时，对象存储的指向虚表的指针

基类的函数前加上**virtual**关键字，在派生类中重写该函数，运行时将会根据所指对象的实际类型来调用相应的函数，如果对象类型是派生类，就调用派生类的函数，如果对象类型是基类，就调用基类的函数。

举个🌰：

```cpp
#include <iostream>
using namespace std;

class Base{
public:
    virtual void fun(){
        cout << " Base::func()" <<endl;
    }
};

class Son1 : public Base{
public:
    virtual void fun() override{
        cout << " Son1::func()" <<endl;
    }
};

class Son2 : public Base{

};

int main()
{
    Base* base = new Son1;
    base->fun();
    base = new Son2;
    base->fun();
    delete base;
    base = NULL;
    return 0;
}
// 运行结果
// Son1::func()
// Base::func()
```

**虚表指针和虚表结构图**

![img](https://cdn.jsdelivr.net/gh/forthespada/mediaImage2@2.6/202104/C++-36-1.png)

![img](https://cdn.jsdelivr.net/gh/forthespada/mediaImage2@2.6/202104/C++-36-2.png)

**实现多态的过程：**

**（1）**编译器在发现基类中有虚函数时，会自动为每个含有虚函数的类生成一份虚表，该表是一个一维数组，虚表里保存了虚函数的入口地址

**（2）**编译器会在每个对象中保存一个虚表指针，即**vptr**，指向对象所属类的虚表。在构造时，根据对象的类型去初始化虚指针vptr，从而让vptr指向正确的虚表，从而在调用虚函数时，能找到正确的函数

**（3）**所谓的合适时机，在派生类定义对象时，程序运行会自动调用构造函数，在构造函数中创建虚表并对虚表初始化。在构造子类对象时，会先调用父类的构造函数，此时，编译器只“看到了”父类，并为父类对象初始化虚表指针，令它指向父类的虚表；当调用子类的构造函数时，为子类对象初始化虚表指针，令它指向子类的虚表

**（4）**当派生类对基类的虚函数没有重写时，派生类的虚表指针指向的是基类的虚表；当派生类对基类的虚函数重写时，派生类的虚表指针指向的是自身的虚表；当派生类中有自己的虚函数时，在自己的虚表中将此虚函数地址添加在后面

这样指向派生类的基类指针在运行时，就可以根据派生类对虚函数重写情况动态的进行调用，从而实现多态性。

### 为什么析构函数一般写成虚函数？

由于类的多态性，基类指针可以指向派生类的对象，如果删除该基类的指针，就会调用该指针指向的派生类析构函数，而派生类的析构函数又自动调用基类的析构函数，这样整个派生类的对象完全被释放。

如果析构函数不被声明成虚函数，则编译器实施静态绑定，在删除基类指针时，只会调用基类的析构函数而不调用派生类析构函数，这样就会造成派生类对象析构不完全，造成内存泄漏。

### 构造函数能否声明为虚函数或者纯虚函数，析构函数呢？

析构函数：

- 析构函数可以为虚函数，并且一般情况下基类析构函数要定义为虚函数。
- 只有在基类析构函数定义为虚函数时，调用操作符delete销毁指向对象的基类指针时，才能准确调用派生类的析构函数（从该级向上按序调用虚函数），才能准确销毁数据。
- **析构函数可以是纯虚函数**，含有纯虚函数的类是抽象类，此时不能被实例化。但派生类中可以根据自身需求重新改写基类中的纯虚函数。

构造函数：

- 构造函数不能定义为虚函数。在构造函数中可以调用虚函数，不过此时调用的是正在构造的类中的虚函数，而不是子类的虚函数，因为此时子类尚未构造好。
- 虚函数对应一个vtable(虚函数表)，类中存储一个vptr指向这个vtable。如果构造函数是虚函数，就需要通过vtable调用，可是对象没有初始化就没有vptr，无法找到vtable，所以构造函数不能是虚函数。

### 基类的虚函数表存放在内存的什么区，虚表指针vptr的初始化时间

- 虚函数表是函数指针的静态数组，因此同一类的不同实例可以共享该 vtable。C++中**虚函数表位于只读数据段（.rodata），也就是C++内存模型中的常量区；而虚函数则位于代码段（.text），也就是C++内存模型中的代码区。**

- 虚表指针vptr跟虚函数密不可分，对于有虚函数或者继承于拥有虚函数的基类，对该类进行实例化时，在构造函数执行时会对虚表指针进行初始化，并且存在对象内存布局的最前面。

### 模板函数和模板类的特例化

**引入原因**

编写单一的模板，它能适应多种类型的需求，使每种类型都具有相同的功能，但对于某种特定类型，如果要实现其特有的功能，单一模板就无法做到，这时就需要模板特例化

**定义**

对单一模板提供的一个特殊实例，它将一个或多个模板参数绑定到特定的类型或值上

**（1）模板函数特例化**

必须为原函数模板的每个模板参数都提供实参，且使用关键字template后跟一个空尖括号对<>，表明将原模板的所有模板参数提供实参，举例如下：

```cpp
template<typename T> //模板函数
int compare(const T &v1, const T &v2)
{
    if(v1 > v2) return -1;
    if(v2 > v1) return 1;
    return 0;
}
//模板特例化,满足针对字符串特定的比较，要提供所有实参，这里只有一个T
template<> 
int compare(const char* const &v1, const char* const &v2)
{
    return strcmp(p1, p2);
}
```

**本质**

特例化的本质是实例化一个模板，而非重载它。特例化不影响参数匹配。参数匹配都以最佳匹配为原则。例如，此处如果是compare(3,5)，则调用普通的模板，若为compare(“hi”,”haha”)则调用**特例化版本**（因为这个cosnt char*相对于T，更匹配实参类型），注意二者函数体的语句不一样了，实现不同功能。

❗❗❗**注意**

模板及其特例化版本应该声明在同一个头文件中，且所有同名模板的声明应该放在前面，后面放特例化版本。

**（2）类模板特例化**

原理类似函数模板，**不过在类中，我们可以对模板进行特例化，也可以对类进行部分特例化。**对类进行特例化时，仍然用template<>表示是一个特例化版本，例如：

```cpp
template<>
class hash<sales_data>
{
    size_t operator()(sales_data& s);
    //里面所有T都换成特例化类型版本sales_data
    //按照最佳匹配原则，若T != sales_data，就用普通类模板，否则，就使用含有特定功能的特例化版本。
};
```

**类模板的部分特例化**

不必为所有模板参数提供实参，可以**指定一部分而非所有模板参数**，一个类模板的部分特例化本身仍是一个模板，使用它时还必须为其特例化版本中未指定的模板参数提供实参(特例化时类名一定要和原来的模板相同，只是参数类型不同，按最佳匹配原则，哪个最匹配，就用相应的模板)

**特例化类中的部分成员**

**可以特例化类中的部分成员函数而不是整个类**，举个🌰：

```cpp
template<typename T>
class Foo
{
    void Bar();
    void Barst(T a)();
};

template<>
void Foo<int>::Bar()
{
    //进行int类型的特例化处理
    cout << "我是int型特例化" << endl;
}

Foo<string> fs;
Foo<int> fi;//使用特例化
fs.Bar();//使用的是普通模板，即Foo<string>::Bar()
fi.Bar();//特例化版本，执行Foo<int>::Bar()
//Foo<string>::Bar()和Foo<int>::Bar()功能不同
```

### 构造函数、拷贝构造函数和赋值操作符的区别

**构造函数**

对象不存在，没用别的对象初始化，在创建一个新的对象时调用构造函数

**拷贝构造函数**

对象不存在，但是使用别的已经存在的对象来进行初始化

**赋值运算符**

对象存在，用别的对象给它赋值，这属于重载“=”号运算符的范畴，“=”号两侧的对象都是已存在的

举个🌰：

```cpp
#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "我是构造函数" << endl;
    }
    A(const A& a)
    {
        cout << "我是拷贝构造函数" << endl;
    }
    A& operator = (A& a)
    {
        cout << "我是赋值操作符" << endl;
        return *this;
    }
    ~A() {};
};

int main()
{
    A a1; //调用构造函数
    A a2 = a1; //调用拷贝构造函数
    a2 = a1; //调用赋值操作符
    return 0;
}
//输出结果
//我是构造函数
//我是拷贝构造函数
//我是赋值操作符
```

### 什么是虚拟继承

[c++虚继承，多继承 ](https://juejin.cn/post/6934281520181952519)

## STL

### 左值引用和右值引用

[左值、右值、右值引用详解](https://blog.csdn.net/hyman_yx/article/details/52044632)

**左值和右值**

左值：表示的是可以获取地址的表达式，它能出现在赋值语句的左边，对该表达式进行赋值。但是修饰符const的出现使得可以声明如下的标识符，它可以取得地址，但是没办法对其进行赋值

```cpp
const int& a = 10;
```

右值：表示无法获取地址的对象，有常量值、函数返回值、lambda表达式等。无法获取地址，但不表示其不可改变，当定义了右值的右值引用时就可以更改右值。

**左值引用和右值引用**

左值引用：传统的C++中引用被称为左值引用

右值引用：C++11中增加了右值引用，右值引用关联到右值时，右值被存储到特定位置，右值引用指向该特定位置，也就是说，右值虽然无法获取地址，但是右值引用是可以获取地址的，该地址表示临时对象的存储位置

**这里主要说一下右值引用的特点：**

- 特点1：通过右值引用的声明，右值又“重获新生”，其生命周期与右值引用类型变量的生命周期一样长，只要该变量还活着，该右值临时量将会一直存活下去
- 特点2：右值引用独立于左值和右值。意思是右值引用类型的变量可能是左值也可能是右值
- 特点3：T&& t在发生自动类型推断的时候，它是左值还是右值取决于它的初始化。

举个🌰：

```C++
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void fun(T&& t)
{
    cout << t << endl;
}

int getInt()
{
    return 5;
}

int main() {

    int a = 10;
    int& b = a;  //b是左值引用
    int& c = 10;  //错误，c是左值不能使用右值初始化
    int&& d = 10;  //正确，右值引用用右值初始化
    int&& e = a;  //错误，e是右值引用不能使用左值初始化
    const int& f = a; //正确，左值常引用相当于是万能型，可以用左值或者右值初始化
    const int& g = 10;//正确，左值常引用相当于是万能型，可以用左值或者右值初始化
    const int&& h = 10; //正确，右值常引用
    const int& aa = h;//正确
    int& i = getInt();  //错误，i是左值引用不能使用临时变量（右值）初始化
    int&& j = getInt();  //正确，函数返回值是右值
    fun(10); //此时fun函数的参数t是右值
    fun(a); //此时fun函数的参数t是左值
    return 0;
}
```

### vector 底层原理及其相关面试题

[vector 底层原理及其相关面试题](https://www.iamshuaidi.com/2299.html)

### list 底层原理及其相关面试题

[list 底层原理及其相关面试题](https://www.iamshuaidi.com/2301.html)

### deque底层原理及其相关面试题

[deque底层原理及其相关面试题](https://www.iamshuaidi.com/2303.html)

### map 、set、multiset、multimap 底层原理及其相关面试题

[map 、set、multiset、multimap 底层原理及其相关面试题](https://www.iamshuaidi.com/2324.html)

### unordered_map、unordered_set 底层原理及其相关面试题

[unordered_map、unordered_set 底层原理及其相关面试题](https://www.iamshuaidi.com/2326.html)

### 迭代器的底层机制和失效的问题

[迭代器的底层机制和失效的问题](https://www.iamshuaidi.com/2328.html)

### STL中hashtable的实现？

[map和unordered_map的区别](https://zhuanlan.zhihu.com/p/210458185)

STL中的hashtable使用的是**开链法**解决hash冲突问题，如下图所示。

![img](https://cdn.jsdelivr.net/gh/forthespada/mediaImage1@1.6.4.2/202102/1566639786045.png)

hashtable中的bucket所维护的list既不是list也不是slist，而是其自己定义的由hashtable_node数据结构组成的linked-list，而bucket聚合体本身使用vector进行存储。hashtable的迭代器只提供前进操作，不提供后退操作

在hashtable设计bucket的数量上，其内置了28个质数[53, 97, 193,...,429496729]，在创建hashtable时，会根据存入的元素个数选择大于等于元素个数的质数作为hashtable的容量（vector的长度），其中每个bucket所维护的linked-list长度也等于hashtable的容量。如果插入hashtable的元素个数超过了bucket的容量，就要进行重建table操作，即找出下一个质数，创建新的buckets vector，重新计算元素在新hashtable的位置。

### 容器内部删除一个元素

1) 顺序容器（序列式容器，比如vector、deque）

erase迭代器不仅使所指向被删除的迭代器失效，而且使被删元素之后的所有迭代器失效(list除外)，所以不能使用erase(it++)的方式，但是erase的返回值是下一个有效迭代器；

```cpp
It = c.erase(it);
```

2) 关联容器(关联式容器，比如map、set、multimap、multiset等)

erase迭代器只是被删除元素的迭代器失效，但是返回值是void，所以要采用erase(it++)的方式删除元素；

```cpp
c.erase(it++)
```

### map插入方式有哪几种？

1) 用insert函数插入pair数据，

```cpp
mapStudent.insert(pair<int, string>(1, "student_one"));
```

2) 用insert函数插入value_type数据

```cpp
mapStudent.insert(map<int, string>::value_type (1, "student_one"));
```

3) 在insert函数中使用make_pair()函数

```cpp
mapStudent.insert(make_pair(1, "student_one"));
```

4) 用数组方式插入数据

```cpp
mapStudent[1] = "student_one";
```

### 常见容器性质总结？

[标准库中有哪些容器？分别有什么特点？](https://www.iamshuaidi.com/2334.html)

#### 容器

| 名称          | 底层                   | 迭代器     | 特点         |
| ------------- | ---------------------- | ---------- | ------------ |
| vector        | 数组                   | 随机访问   | 类似数组     |
| deque         | 中央控制器和多个缓冲区 | 随机访问   | 首尾快速增删 |
| list          | 双向链表               | 双向迭代器 | 快速增删     |
| set           | 红黑树                 | 双向迭代器 | 有序，不重复 |
| map           | 红黑树                 | 双向迭代器 | 有序，不重复 |
| unordered_set | 哈希表                 | 前向迭代器 | 无序，不重复 |
| unordered_map | 哈希表                 | 前向迭代器 | 无序，可重复 |

#### 适配器

| 名称               | 底层   | 迭代器     | 特点                     |
| ------------------ | ------ | ---------- | ------------------------ |
| stack              | deque  | 无         | FILO                     |
| queue              | deque  | 无         | FIFO                     |
| priority_queue     | vector | 无         | 优先队列，大顶堆，小顶堆 |
| multiset/multimap  | 红黑树 | 双向迭代器 | 有序，可重复             |
| unordered_multiset | 哈希表 | 前向迭代器 | 无序，可重复             |
| unordered_multimap | 哈希表 | 前向迭代器 | 无序，可重复             |
| forward_list       | 单链表 | 前向迭代器 | 单链表的特点             |

### STL中迭代器失效的情况有哪些？

**插入元素：**

1、尾后插入：size < capacity时，首迭代器不失效尾迭代失效（未重新分配空间），size == capacity时，所有迭代器均失效（需要重新分配空间）。

2、中间插入：中间插入：size < capacity时，首迭代器不失效但插入元素之后所有迭代器失效，size == capacity时，所有迭代器均失效。

**删除元素：**

尾后删除：只有尾迭代失效。

中间删除：删除位置之后所有迭代失效。

deque 和 vector 的情况类似,

而list双向链表每一个节点内存不连续, 删除节点仅当前迭代器失效,erase返回下一个有效迭代器;

map/set等关联容器底层是红黑树删除节点不会影响其他节点的迭代器, 使用递增方法获取下一个迭代器 mmp.erase(iter++);

unordered_(hash) 迭代器意义不大, rehash之后, 迭代器应该也是全部失效.

### STL内存优化？

STL内存管理使用二级内存配置器。

**(1) 第一级配置器：**

第一级配置器以malloc()，free()，realloc()等C函数执行实际的内存配置、释放、重新配置等操作，并且能在内存需求不被满足的时候，调用一个指定的函数。一级空间配置器分配的是大于128字节的空间，如果分配不成功，调用句柄释放一部分内存，如果还不能分配成功，抛出异常。

第一级配置器只是对malloc函数和free函数的简单封装，在allocate内调用malloc，在deallocate内调用free。同时第一级配置器的oom_malloc函数，用来处理malloc失败的情况。

**(2) 第二级配置器：**

第一级配置器直接调用malloc和free带来了几个问题：

- 内存分配/释放的效率低
- 当配置大量的小内存块时，会导致内存碎片比较严重
- 配置内存时，需要额外的部分空间存储内存块信息，所以配置大量的小内存块时，还会导致额外内存负担

如果分配的区块小于128bytes，则以内存池管理，第二级配置器维护了一个自由链表数组，每次需要分配内存时，直接从相应的链表上取出一个内存节点就完成工作，效率很高

自由链表数组：自由链表数组其实就是个指针数组，数组中的每个指针元素指向一个链表的起始节点。数组大小为16，即维护了16个链表，链表的每个节点就是实际的内存块，相同链表上的内存块大小都相同，不同链表的内存块大小不同，从8一直到128。如下所示，obj为链表上的节点，free_list就是链表数组。

内存分配：allocate函数内先判断要分配的内存大小，若大于128字节，直接调用第一级配置器，否则根据要分配的内存大小从16个链表中选出一个链表，取出该链表的第一个节点。若相应的链表为空，则调用refill函数填充该链表。默认是取出20个数据块。

填充链表 refill：若allocate函数内要取出节点的链表为空，则会调用refill函数填充该链表。refill函数内会先调用chunk_alloc函数从内存池分配一大块内存，该内存大小默认为20个链表节点大小，当内存池的内存也不足时，返回的内存块节点数目会不足20个。接着refill的工作就是将这一大块内存分成20份相同大小的内存块，并将各内存块连接起来形成一个链表。

内存池：chunk_alloc函数内管理了一块内存池，当refill函数要填充链表时，就会调用chunk_alloc函数，从内存池取出相应的内存。

- 在chunk_alloc函数内首先判断内存池大小是否足够填充一个有20个节点的链表，若内存池足够大，则直接返回20个内存节点大小的内存块给refill；
- 若内存池大小无法满足20个内存节点的大小，但至少满足1个内存节点，则直接返回相应的内存节点大小的内存块给refill；
- 若内存池连1个内存节点大小的内存块都无法提供，则chunk_alloc函数会将内存池中那一点点的内存大小分配给其他合适的链表，然后去调用malloc函数分配的内存大小为所需的两倍。若malloc成功，则返回相应的内存大小给refill；若malloc失败，会先搜寻其他链表的可用的内存块，添加到内存池，然后递归调用chunk_alloc函数来分配内存，若其他链表也无内存块可用，则只能调用第一级空间配置器。

## 参考资料

[C++面试题分类阅读指南](https://www.iamshuaidi.com/2309.html)

[阿秀的求职笔记 ](https://interviewguide.cn/)

[第 1 章 迈向现代 C++ 现代 C++ 教程: 高速上手 C++ 11/14/17/20)](https://changkun.de/modern-cpp/zh-cn/01-intro/)

《C++ Primer Plus》

《C++ Primer》

《C/C++标准库》

《程序员的自我修养》

《深入理解计算机系统》