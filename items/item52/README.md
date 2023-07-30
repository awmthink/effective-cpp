# Item 52: 写了placement new也要写placement delete

* 当你写一个placement operator new，请确定也写出了对应的placement operator delete。如果没有这样做，你的程序可能会发生隐微而时断时续的内存泄漏。
* 当你声明了placement new和placement delete，请确定不要无意识地遮掩了它们的正常版本。

`new`分为2步，第一步分配内存（调用`operator new`），第二步调用构造函数，如果调用构造函数过程中，发生了异常，编译器会自动的调用`operator delete`来释放已经申请的内存。但如果我们使用提是`placement operator new`，但没有提供对应的placement delete的话，编译器就不知道该如何处理已经分配好的内存了，于是什么也不做。

也就是说placement delete只有在“伴随platement new调用而触发的构造函数“出现异常时才会被调用，如果对象被正确的分配创建，那么释放的时候，调用的则是普通版本的`operator delete`。

成员函数的名称hidding问题在继承体系下定制operator new/delte也存在：

```cpp
class Base {
public:
  staitc void* operator new(std::size_t std::ostream& logStream);
};

Base *pb = new Base; // 错误！因为正常形式的operator new被掩盖
Base *pb = new (std::cerr) Base; // 正确
```

同样的道理，derived classes中的operator new会掩盖global版本和继承而得到的opeator new版本。

```cpp
class Derived: public Base {
public:
  static void* operator new(std::size_t size);
};

Derived *pd = new (std::cerr) Dervied; // 错误，因为Base的placement new被掩盖了
Derived *pd = new Derived; // 设问题
```

避免上面这样问题的做法，可以是提供一个base class，内含所有正常形式的new和delete，这些new和delete都是直接调用全局的。

```cpp
class StandardNewDeleteForms {
  static void *operator new(std::size_t size) { return ::operator new(size); }
  // delete, sized-delete, nothrow, ....
};

class Widget: public StandNewDeleteForms {
public:
  // 利用继承机制和using声明式
  using StandNewDeleteForms::operator new;
  using StandNewDeleteForms::operator delete;
};
```


