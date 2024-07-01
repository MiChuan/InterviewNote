# 智能指针

## scoped_ptr

不能被复制或赋值给其他 `scoped_ptr` 对象，不能与其他指针比较 (除了 nullptr)

### scoped_ptr 用例

```cpp
template <typename T>
class scoped_ptr {
public:
    // 构造函数：初始化 scoped_ptr 并接管指针的所有权
    explicit scoped_ptr(T* ptr = nullptr) : ptr_(ptr) {}

    // 析构函数：释放管理的对象
    ~scoped_ptr() {
        delete ptr_;
    }

    // 禁止复制构造函数和赋值操作符
    scoped_ptr(const scoped_ptr&) = delete;
    scoped_ptr& operator=(const scoped_ptr&) = delete;

    // 移动构造函数和移动赋值操作符
    scoped_ptr(scoped_ptr&& other) noexcept : ptr_(other.release()) {}
    scoped_ptr& operator=(scoped_ptr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    // 重载解引用操作符
    T& operator*() const {
        return *ptr_;
    }

    // 重载箭头操作符
    T* operator->() const {
        return ptr_;
    }

    // 获取管理的指针
    T* get() const {
        return ptr_;
    }

    // 释放管理的指针并返回
    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    // 重置管理的指针
    void reset(T* ptr = nullptr) {
        if (ptr_ != ptr) {
            delete ptr_;
            ptr_ = ptr;
        }
    }

    // 检查是否管理一个非空指针
    explicit operator bool() const {
        return ptr_ != nullptr;
    }

private:
    T* ptr_;
};
```

## unique_ptr

头文件＜boost/smart_ptr/make_unique.hpp＞里实现了make_unique（）函数，位于名字空间 boost 而不是 std，为了避免潜在的冲突。

### unique_ptr 用例

#### 创建单个对象

```cpp
#include <memory>

struct MyClass {
    MyClass(int x, double y) : x_(x), y_(y) {}
    int x_;
    double y_;
};

int main() {
    auto ptr = std::make_unique<MyClass>(42, 3.14);
    // ptr is a std::unique_ptr<MyClass>
    return 0;
}
```

#### 创建数组

```cpp
#include <memory>

int main() {
    auto arr = std::make_unique<int[]>(10);
    // arr is a std::unique_ptr<int[]> with 10 elements
    return 0;
}
```

#### 函数中返回动态分配的对象

```cpp
#include <memory>

std::unique_ptr<int> createInt(int value) {
    return std::make_unique<int>(value);
}

int main() {
    auto ptr = createInt(42);
    // ptr is a std::unique_ptr<int>
    return 0;
}
```

#### 容器中存储动态分配的对象

```cpp
#include <memory>
#include <vector>

int main() {
    std::vector<std::unique_ptr<int>> vec;
    vec.push_back(std::make_unique<int>(1));
    vec.push_back(std::make_unique<int>(2));
    vec.push_back(std::make_unique<int>(3));
    // vec contains std::unique_ptr<int> elements
    return 0;
}
```

#### 避免资源泄漏

```cpp
#include <memory>

void process(std::unique_ptr<int> ptr) {
    // Do something with ptr
}

int main() {
    auto ptr = std::make_unique<int>(42);
    process(std::move(ptr)); // No need to manually delete the pointer
    return 0;
}
```

## shared_ptr

引用计数型的智能指针，可以被自由地拷贝和赋值，可以在任意的地方共享它，当没有代码使用它时（引用计数为0），才删除被包装的动态分配的对象。

### shared_ptr 用例

#### 创建单个对象

```cpp
#include <memory>

struct MyClass {
    MyClass(int x, double y) : x_(x), y_(y) {}
    int x_;
    double y_;
};

int main() {
    auto ptr = std::make_shared<MyClass>(42, 3.14);
    // ptr is a std::shared_ptr<MyClass>
    return 0;
}
```

- 函数中返回动态分配的对象
- 容器中存储动态分配的对象
- 避免资源泄漏

#### 创建数组（C++20）

```cpp
#include <memory>

int main() {
    auto arr = std::make_shared<int[]>(10);
    // arr is a std::shared_ptr<int[]> with 10 elements
    return 0;
}
```

### shared_ptr 应用于标准容器

#### shared_ptr 作为容器的元素

```cpp
#include <iostream>
#include <memory>
#include <vector>

class MyClass {
public:
    MyClass(int id) : id_(id) {
        std::cout << "Constructing MyClass " << id_ << std::endl;
    }
    ~MyClass() {
        std::cout << "Destroying MyClass " << id_ << std::endl;
    }
    void print() const {
        std::cout << "MyClass " << id_ << std::endl;
    }
private:
    int id_;
};

int main() {
    std::vector<std::shared_ptr<MyClass>> vec;

    // 创建并存储 shared_ptr 对象
    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::make_shared<MyClass>(i));
    }

    // 使用 shared_ptr 对象
    for (const auto& ptr : vec) {
        ptr->print();
    }

    return 0;
}
```

#### 容器作为 shared_ptr 的管理对象

```cpp
#include <iostream>
#include <memory>
#include <vector>

class MyClass {
public:
    MyClass(int id) : id_(id) {
        std::cout << "Constructing MyClass " << id_ << std::endl;
    }
    ~MyClass() {
        std::cout << "Destroying MyClass " << id_ << std::endl;
    }
    void print() const {
        std::cout << "MyClass " << id_ << std::endl;
    }
private:
    int id_;
};

int main() {
    // 创建一个 shared_ptr 管理 vector 容器
    auto vecPtr = std::make_shared<std::vector<std::shared_ptr<MyClass>>>();

    // 向 vector 中添加 MyClass 对象
    for (int i = 0; i < 5; ++i) {
        vecPtr->push_back(std::make_shared<MyClass>(i));
    }

    // 使用 vector 中的 MyClass 对象
    for (const auto& ptr : *vecPtr) {
        ptr->print();
    }

    return 0;
}
```

### 桥接模式

```cpp
#include <iostream>
#include <memory>

// 渲染器接口
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void renderCircle(float x, float y, float radius) = 0;
    virtual void renderRectangle(float x, float y, float width, float height) = 0;
};

// OpenGL 渲染器
class OpenGLRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float radius) override {
        std::cout << "OpenGL rendering circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    void renderRectangle(float x, float y, float width, float height) override {
        std::cout << "OpenGL rendering rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

// DirectX 渲染器
class DirectXRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float radius) override {
        std::cout << "DirectX rendering circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    void renderRectangle(float x, float y, float width, float height) override {
        std::cout << "DirectX rendering rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

// 形状接口
class Shape {
public:
    Shape(std::shared_ptr<Renderer> renderer) : renderer_(renderer) {}
    virtual ~Shape() = default;
    virtual void draw() = 0;
protected:
    std::shared_ptr<Renderer> renderer_;
};

// 圆形
class Circle : public Shape {
public:
    Circle(std::shared_ptr<Renderer> renderer, float x, float y, float radius)
        : Shape(renderer), x_(x), y_(y), radius_(radius) {}
    void draw() override {
        renderer_->renderCircle(x_, y_, radius_);
    }
private:
    float x_, y_, radius_;
};

// 矩形
class Rectangle : public Shape {
public:
    Rectangle(std::shared_ptr<Renderer> renderer, float x, float y, float width, float height)
        : Shape(renderer), x_(x), y_(y), width_(width), height_(height) {}
    void draw() override {
        renderer_->renderRectangle(x_, y_, width_, height_);
    }
private:
    float x_, y_, width_, height_;
};

int main() {
    auto openglRenderer = std::make_shared<OpenGLRenderer>();
    auto directxRenderer = std::make_shared<DirectXRenderer>();

    Circle circle1(openglRenderer, 10, 10, 5);
    Rectangle rectangle1(openglRenderer, 20, 20, 15, 10);

    Circle circle2(directxRenderer, 30, 30, 7);
    Rectangle rectangle2(directxRenderer, 40, 40, 20, 15);

    circle1.draw();
    rectangle1.draw();
    circle2.draw();
    rectangle2.draw();

    return 0;
}
```

## weak_ptr

不具有普通指针的行为，没有重载 operator* 和 -＞。weak_ptr 被设计为与 shared_ptr 协同工作，可以从一个 shared_ptr 或另一个 weak_ptr 对象构造以获得资源的观测权。但 weak_ptr 没有共享资源，它的构造不会引起指针引用计数的增加。

### weak_ptr 用例

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;

    if (auto locked = weak.lock()) {
        std::cout << "Object still exists: " << *locked << std::endl;
    } else {
        std::cout << "Object has been destroyed." << std::endl;
    }

    shared.reset(); // 释放 shared_ptr，对象被销毁

    if (auto locked = weak.lock()) {
        std::cout << "Object still exists: " << *locked << std::endl;
    } else {
        std::cout << "Object has been destroyed." << std::endl;
    }

    return 0;
}
```

### 打破循环引用

```cpp
class node
{
public:
    ~node()
    {
        std::cout << "deleted" << std::endl;
    }

    typedef weak_ptr<node> ptr_type;
    //typedef shared_ptr<node> ptr_type;
    ptr_type next;
};

void case3()
{
    auto p1 = make_shared<node>();
    auto p2 = make_shared<node>();

    p1->next = p2;
    p2->next = p1;

    assert(p1.use_count() == 1);
    assert(p2.use_count() == 1);

    if(!p1->next.expired())
    {
        auto p3 = p1->next.lock();
    }
}
```

