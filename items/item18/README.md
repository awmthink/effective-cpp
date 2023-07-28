# Item 18: 让接口容易被正确使用，不易被误用

* 好的接口很容易被正确使用，不容易被误用。你应用在你所有接口中努力达成这些性质。
* 促进正确使用的办法包括接口的一致性，以及与内置类型的行为兼容。
* 阻止误用的办法包括建立新的类型、限制类型上的操作、束缚对象的值，以及消除客户的资源管理的责责任。
* shared_ptr支持定制删除器。这可防范跨DLL的问题，可被用来自动解除互斥所等等。

```cpp
class Data {
public:
  Data(int month, int day, int year);
};
```

对于上面`Data`的构造函数，用户可能很容易把month，day等值传反，或者因为手误传入不正确的范围。我们可以通过专入新的类型来解决。

```cpp
struct Day;
struct Month;
struct Year;

class Data {
public:
  Data(Month month, Day day, Year year);
};
```

如何约束类型的值范围呢，像Month这样的类型，使用限定作用域的enum，或者使用static函数：

```cpp
enum class Month {
    Jan, Feb, ..., Dec
};

class Month {
public:
  static Month Jan() { return Month(1); }
  static Month Feb() { return Month(1); }
  ...
  static Month Dec() { return Month(1); }
};
```

我们应该避免与内置类型不兼容，提供行为一致的接口，比如STL的容器接口十分一致，每个容器都有size的成员函数，返回窗口中有多少对象。

任何接口如果要求客户端必须记得做某些事件，就是有着“不正确使用”的倾向。例如，返回内部动态分配内存的指针的接口：

```cpp
Investment* createInvestment();
```

它需要调用者时时刻刻记得要手动释放返回的指针。

良好的设计是使用`std::shared_ptr`来管理返回的指针。这样还可以避免cross-DLL的内存问题，由于每个 DLL 都有自己的独立地址空间，因此在一个 DLL 中分配的内存不能直接在另一个 DLL 中释放，否则可能导致内存泄漏或访问无效内存的问题。
