# Item 27: 尽可能少做转型动作

* 如果可以，尽量避免转型，特别是在关注效率的代码中避免dynamic_casts，如果有设计需要转型动作，试着发展无需转型的替代设计。
* 如果转型是必要的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，而不需将转型放进它们自己的代码中。
* 宁可使用C++ Style的转型，不要使用旧式转型，前者很容易辨识出来，而且也比较有着分门别类的职掌。

转型（casts）破坏了类型系统（type system）。C风格的转型有2种形式：

```cpp
(T) experssion; // 将expression转型为T

T(expression); // 函数风格的转型，将expression转型为T
```
两种形式并没有差别。我们把这两种称为“旧式转型”（old-style casts）

C++中提供了四种新式的转换，被称为new-style casts

* `const_cast`：用于将对象的常量性移除，只有它有这样的功能。
* `dynamic_cast`：主要用来执行“安全向下转型”（safe dwoncasting），也就是用来决定某对象是否归属继承体系中某个类型。
* `reinterpret_cast`: 进行底层存储空间的指针类型转换。
* `static_cast`：强迫进行隐式转换，可以用于将non-const对象转为const对象，将int转为double等等，也可以void*指针转换为typed指针。

许多程序员相信，转型其实什么都没做，只是告诉编译器把某种类型视为另一种类型。这是一种错误观念，任何一个类型转换（不论是通过转型操作而进行的显式转换，或通过编译器完成的隐式转换）往往真的产生运行期的代码。

```cpp
class Widget {
pulbic:
  explicit Widget(int size);
};
doSomeWork(static_cast<Widget>(15)); // 这个转型动作会导致Widget的构造函数被调用。

int x, y;
double d = static_cast<double>(x) / y;  // 由于int和double底层表达不同，对x的转换，编译器会对x的底层进行重写

class Base {};
class Derived: public Base {};
Derived d;
Base *pb = &d; // 隐式的把 Derived* 转换为了 Base*，编译器可能要进行指针的偏移计算
```

这里我们不过是建立-base class 指针指向一个 derived class 对象，但有时候上述的两个指针值并不相同。这种情况下会有个偏移量(offset)在运行期被施行于Derived* 指针身上，用以取得正确的 Base* 指针值。单一对象(例如一个类型为 Derived的对象)可能拥有一个以上的地址（例如“以 Base* 指向它”时的地址和“以 Derived*指向它”时的地址，C 不可能发生这种事，Java 不可能发生这种事，C# 也不可能发生这种事。但 C++ 可实际上一旦使用多重继承，这事几乎一直发生着。即使在单一继承中也可能发生。

但请记住，对象的布局方式和它们的地址计算方式随着编译器的不同而不同，那意味着，你不能因为知道了对象的内存布局，而自己来通过偏移计算来进行转型。这通常会产生难以跨平台的代码。

下面再来看一下在Dervied类中调用Based类方法的例子：

```cpp
class Window{
public:
    virtual void onResize();
};

class SpecialWindow :public Window{
public:
    virtual void onResize()
    {
        static_cast<Window>(*this).onResize(); // 将*this转型为Window，然后调用其onResize
        // ... SpecialWindow专属动作
    }
};
```

我们在`SpecialWindow`的`onResize`函数中，先调用了基类的`onResize`函数，但可惜的是，这个调用并不成功，因为`static_cast<Window>(*this)`得到的是一个临时对象，我们在这个临时对象上调用onResize，并不会影响当前的`SpecialWindow`对象。正确的做法是：

```cpp
class SpecialWindow :public Window{
public:
    virtual void onResize()
    {
        Windows::onResize();
        // ... SpecialWindow专属动作
    }
};
```

最后我们来看dynamic_cast，之所以需要 dynamic cast，通常是因为你想在一个你认定为 derived class 对象身上执行 derived class 操作函数，但你的手上却只有一个“指向 base”的 pointer或reference，你只能靠它们来处理对象。

dynamic_cast的内部实现往往通过RAII，然后与目标类型进行匹配，需要在整个继承体系上进行字符串匹配，所以效率很低。

如果是对基类的引用进行dynamic_cast，失败的话，会抛出std::bad_cast类型的异常，如果是对基类的指针进行dynamic_cast，失败的话，返回一个空指针。