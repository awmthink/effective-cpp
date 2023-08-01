# 绝不重新定义继承而来的缺省参数值

* 绝对不要重新定义一个继承而来的缺省参数值，因为virtual函数的调用是动态绑定的，而缺省的参数值却是静态绑定的。

```cpp
class Shape {
public:
    enum ShapeColor {Red, Green, Blue};
    virtual void draw(ShapeColor color=Red) const  = 0;
};

class Rectangle {
public:
    // 注意，赋予了不同的缺省参数值，这在调用时是无效的。
    virtual void draw(ShapeColor color=Green) const;
};

class Circle {
public:
    // 如果我们是以Circle的对象、指针、引用来调用draw需要指定参数值，因为静态绑定不会继承Base的默认参数
    // 但如果是用基类的指针或引用，则可以不用指定
    virtual void draw(ShapeColor color) const;
};

class Ellipse {
public:
    // 重复代码，引入了依赖性，Base改后，Derived都需要改
    virtual void draw(ShapeColor color=Red) const;
};
```