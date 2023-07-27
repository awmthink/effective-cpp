# Item 07: 为多态基类声明virtual析构函数

* 带多态性质的base class应该声明一个vitual析构函数。如果class带有任何virtual函数，它就应用拥有一个virtual函数。
* Class的设计如果不是作为base class使用，或者不是为了具备多态性，就不应该声明为virtual析构函数。


一般情况下，我们不会想去为我们的类声明一个virtal的析构函数，因为它们增加类对象的存储占用（多个虚表指针）。比如对于像`Point`这样的类。

```cpp
struct Point {
  int x;
  int y;
};
```

但当我们的类一旦有可能被别人继承，大部分情况下需要把析构函数声明为virtual，因为对于一个指向基类的指针，它底层可能指向的是派生类型的对象，如果基类的析构函数不是virtual的，则无法正确的调用到派生类的析构函数，发生未定义的行为，比如derived类特有的成员是没有销毁的。就有可能导致资源泄漏。

为什么上面说大部分情况呢，并非所有的base class的设计都是为了多态，比如像`Uncopyable`或`input_iterator_tag`这样的类。

关于纯虚的析构函数：如果一个类设计为一个接口类，但没有一个普通的成员函数适合作为纯虚函数，则可以将析构函数声明为纯虚函数。

```cpp
class AWOV { // Abstract  w/o Virtuals
public:
  virtual ~AWOV() = 0;
};
AWOV::~AWOV() = default;
```