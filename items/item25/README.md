# Item 25: 考虑写出一个不抛异常的swap函数

* 当std::swap对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常。
* 如果你提供一个member swap，也该提供一个non-member swap来调用前者，对于classes（而非templates），也请特化std::swap。
* 调用swap时应针对std::swap使用using声明式，然后调用swap并且不带任何“命名空间资格修饰”。
* 为“用户定义类型”进行std template全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西。


对于一般的class类型，我们可以定义std::swap的特化版本：

```cpp
namespace std {
// 第2优先级被查找
template <>
void swap<Widget>(Widget &lhs, Widget &rhs) {
  std::cout << "std::swap()" << std::endl;
  lhs.swap(rhs);
}

}  // namespace std
```

但如果Widget是一个类模板，我们再像下面这样定义：

```cpp
namespace std {
// 第2优先级被查找
template <typename T>
void swap<Widget<T>>(Widget<T> &lhs, Widget<T> &rhs) {
  std::cout << "std::swap()" << std::endl;
  lhs.swap(rhs);
}

}  // namespace std
```

因为上面这种语法实际是对`template <typename T> void swap(T&lhs, T&rhs);`的一种偏特化，但函数并不支持偏特化。对于函数偏特化，一般的建议是使用重载：

```cpp
namespace std {
// 第2优先级被查找
template <typename T>
void swap(Widget<T> &lhs, Widget<T> &rhs) {
  std::cout << "std::swap()" << std::endl;
  lhs.swap(rhs);
}

}  // namespace std
```

上面的swap实际上是对`std::swap`原版的一种重载形式。但问题是，std是一个特珠的命名空间，其管理规则比较特珠。客户可以全特化std内的template，但不可以添加新的templates（或classes或functions或其他任何东西）到std里头。std的内容完全由C++标准委员会决定，标准委员会禁止我们膨胀那些已声明好的东西。那么对于类模板来说，剩下的方法就只能是把swap声明为普通的non-member函数。

```cpp

namespace WidgetStuff {

template <typename T>
class Widget {};

template <typename T>
void swap(Widget<T> &lhs, Widget<T> &rhs) {
  std::cout << "std::swap()" << std::endl;
  lhs.swap(rhs);
}
};
```

那是不是任何时候我们都应该使用上面这种方式呢，把swap定义为同一个命名空间下的普通的函数。考虑下面的代码：

```cpp
template<typename T>
void doSomething(T& obj1, T&obj2) {
    ...
    swap(obj1, obj2);
    ...
}
```

在`doSomethig`里，我们应该使用普通的swap，还是应该使用std::swap呢，很有可能类型T没有提供普通的swap呢？一个聪明的做法如下：

```cpp
template<typename T>
void doSomething(T& obj1, T&obj2) {
    using std::swap;
    ...
    swap(obj1, obj2);
    ...
}
```
如果T的普通版本swap可用，则用普通版本，否则将使用std::swap版本（有可能是特化的，也有可能不是）。