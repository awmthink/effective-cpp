# Item 45: 运用成员函数模板接受所有兼容类型

* 请使用member function template（成员函数模板）生成“可接受所有兼容类型”的函数。
* 如果你声明 member templates 用于“泛化copy构造“或“泛化assignment操作“，你还是需要声明正常的copy构造函数或copy assignment操作符。

```cpp
template <class T>
class SharedPointer {
 public:
  // 构造函数
  explicit SharedPointer(T *ptr = nullptr) : pointer_(ptr) {}

  // 拷贝构造函数
  SharedPointer(const SharedPointer &sp) noexcept {}

  // 移动构造函数
  SharedPointer(SharedPointer &&sp) noexcept {}

  // 成员模板函数
  // 如果想要实现通过派生类的智能指针来创建基类的智能指针，则必须使用模板成员函数
  template <class U>
  SharedPointer(const SharedPointer<U> sp) noexcept {} 
};
```

成员模板函数并不改变语言规则，也就是编译器对于copy构造、移动构造等函数的隐式创建规则，也就是即使我们定义了成员模板形式的拷贝构造函数，但没有显式定义普通的拷贝构造，那么编译器还是会合成一个默认的。

