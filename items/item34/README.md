# 区分接口继承和实现继承

* 接口继承和实现继承不同。在public继承之下，derived classes总是继承base class的接口
* 纯虚函数只具体指定接口继承
* 非纯虚函数具体指定接口和继承及缺省的实现继承
* 非虚函数具体指定接口继承和强制实现继承

```cpp
class Shape {
public:
    virtual void draw() const = 0;
    virtual void error(const std::string& msg);
    int objectID() const;
};

class Rectangle: public Shape {...};
class Ellipse: public Shape {...}
```

* 声明一个纯虚函数的目换是为了让derived classes只继承函数的接口。`Shape::draw`就是这个目的，因为所有对象都应该是可以绘出的，所以必须有这个接口，但每个形状的具体的绘画的实现是不同的。
* 声明一个普通的虚函数（非纯）的目的是让derived classes继承该函数的接口和默认实现。对于`Shape`的派生类，在处理过程中遇到了错误，可以自由处理，如果某个class不想针对错误做出任何特殊行为，它可以退回到Shape clas提供的确省的错误处理行为。这正是`Shape::error()`的声明形式。

但有时候，我们可以会担心有一些派生类可能会滥用默认实现，也就是明明不适全用默认实现，但它忘记提供自己的特珠版本了，我们为了提醒它，可以让这个动作显式一些：

```cpp
class Shape {
public:
    virtual void error(const std::string& msg) = 0;
protected:
    void defaultError(const std::sting& msg); 
}

class void Elssipse::error(const std::string& msg) {
    Shape::defaultError(msg);
}
```

因为把`error`声明为了纯虚函数，所有的派生类现在都必须实现它，避免遗忘。

还有一种方法是利用纯虚函数也可以有其默认实现的技术：

```cpp
class Shape {
public:
    virtual void error(const std::string& msg) = 0;
}

void Shape::error(const std::string& msg) {
    // 缺省的实现
}

class void Elssipse::error(const std::string& msg) {
    Shape::error(msg);
}
```

* 声明为non-virtual函数的目换是为了令derived classes继承函数的接口以及一份强制实现。`Shape::ObjectID()`的声明想做的是：每一个Shape对象都有一个用来产生对象识别码的函数；此识别码总是采用相同计算方案，该方法由Shape::objectID()的定义决定，任何derived class都不应该尝试改变其行为。