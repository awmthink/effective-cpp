# Item33: 避免遮掩继承而来的名称

* derived classes内的名称会遮掩base classes内的名称。在public继承下从来没有人希望如何。
* 为了让被遮掩的名称再见天日，可以使用using声明式或转发函数（forwarding functions）。

我们都知道作用域下的变量的遮掩规则：内层作用域会遮掩外围作用域的名称：

```cpp
int x;  // global变量
void someFunc() {
    double x; // local变量
    std::cin >> x;  // 读一个新值赋予local变量x
}
```

读取语句赋予的是local变量x，而不是global变量x。当编译器处理someFunc的作用域内并遭遇名称x时，它在local作用域查找是否有什么东西带着这个名称。如果找到就不再找其他作用域。这里虽然global作用域下的x是int类型，而global作用域下的是int类型，但那不要紧。C++的**名称遮掩规则（name-hiding rules）**所做的唯一的事情就是：遮掩名称。（忽略类型）

在继承体系下的名称遮掩问题：

```cpp
class Base {
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int);
    virtual void mf2();
    void mf3();
    void mf3(double);
};

class Derived: public Base {
public:
    virtual void mf1();
    void mf3();
    void mf4();
};

Dervied d;
int x;

d.mf1();    // OK，调用 Derived::mf1()
d.mf1(x);   // 错误！因为Derived::mf1()遮掩了Base::mf1(int)
d.mf2();    // OK, 调用 Base::mf2()
d.mf3();    // OK, 调用 Derived::mf3()
d.mf3(x);   // 错误！因为Derived::mf3()遮掩了Base::mf1(double)
```

Derived的成员函数会遮掩基类的同名函数的原因是：base和derived class之间是is-a的关系，Derived应该完全继承那些重载的函数。我们可以使用using声明来显式的继承所有重载函数。

```cpp
class Derived: public Base {
public:
    using Base::mf1();
    using Base::mf3();
    virtual void mf1();
    void mf3();
    void mf4();
};
```

有时候，我们并不想继承base classes的所有函数，在public继承下当然不可能发生，但在private继承下则很常见。比如对于`mf1`，我们只希望继承那个无参数的版本：

```cpp
class Derived: public Base {
public:
    virtual void mf1() { // 转交函数
        Base::mf1(); // 隐式的inline
    }
};
```