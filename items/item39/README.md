# Item 39: 明智而审慎地使用private继承

* private继承意味着is-implemented-in-terms-of。它通常比复合使用的优先级低。但当derived class需要访问base的protected成员，或需要重机关报定义继承而来的虚函数时，这么设计是合理的。
* 和复合不同，private继承可以进行empty base最优化。这对于致力于对象尺寸最小化的程序库开发者而言，可能很重要。

回到条款32的例子，我们把Student和Person之间的关系改为private继承：

```cpp
class Person {};
class Student: private Person {};

void eat(const Person &p);

Person p;
Student s;

eat(p);     // OK
eat(s);     // 错误，难道Student不是Person吗？
```

从编译器的角度：如果class之间的关系是private，编译器不会自动将一个derived class对象转换为base class对象。想一下，base class中的public接口在private继承下，在derived中都变成了private接口了，那么就没办法执行像base一样的行为了。

现在让我们开始讨论其意义。Private 继承意味 implemented-in-terms-of（根据某物实现出）。如果你让class A以private形式继承class B，你的用意是为了采用class B 内已经备妥的某些特性，不是因为B对象和A对象存在有任何观念上的关系。private 继承纯粹只是一种实现技术（这就是为什么继承自一个private base class 的每样东西在你的 class 内都是 private： 因为它们都只是实现枝节而己）。

借用条款 34 提出的术语，private 继承意味只有实现部分被继承，接口部分应略去。如果A以private 形式继承B，意思是A对象根据B对象实现而得，再没有其他意涵了。Private 继承在软件“设计” 层面上没有意义，其意义只及于软件实现层面。

那么private继承和复合有什么不同呢？答案很简单：尽可能使用复合，必要时才使用private继承。主要是当protected成员或virtual函数牵扯进来的时候。另外就是使用Private继承来优化类的占用空间。

```cpp
class Timer {
public:
    explicit Timer(int tickFrequency);
    virtual void onTick() const;
};

class Widget: private Timer {
private:
    virtual void onTick() const;
}
```

`Timer`是一个我们工具箱中的类，按某个频率进行滴答前进，每次滴答就会触发调用了某个虚函数：`onTick`。现在我们`Widget`想使用`Timer`的功能，但触发的具体行为希望能自定义，那么我们就可以使用private继承的方式，并重写`onTick`函数。这在组合的方式下，就不容易实现。

但上面的实现并不是惟一的方式，我们可以用复合取而代之。

```cpp
class Widget {
private:
    class WidgetTimer: public Timer {
    public:
        virtual void onTick() const;
    };
    WidgetTimer timer;    
};
```

这种设计更加复杂一些，但充分说明，解决问题的方式往往不止一种。private继承没有非用不可的场景。而且上面这种实现方式，我们可以实现编译依赖分离，`Widget`的头文件就不需要include Timer的头文件了，我们可以把`WidgetTimer timer`改为：`WidgetTimer* timer`，然后把`WidgetTimer`的实现移出去。


下面说明private继承的第二个主要应用场景：

```cpp
class Empty {};
class HoldsAnInt {
private:
    int x;
    Empty e;
};
std::cout << sizeof(HoldsAnInt) << std::endl; // 8


class HoldsAnInt: private Empty {
private:
    int x;
};
std::cout << sizeof(HoldsAnInt) << std::endl; // 4
```

这就是所谓的EBO（empty base optimization；空白基类优化）。现实中"emtpy" class并不真的是empty，它们内部可能含有typedefs，enums，static成员变量，或non-virtual函数等。

