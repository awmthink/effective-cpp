# Item 46: 需要类型转换时请为模板定义非成员函数

* 当编写一个class template时，它所提供之“与此template相关的”函数支持“所有参数之隐式类型转换”时，请将那些函数定义为class template内部的friend函数。

[条款24](../item24/README.md)提到过为什么`non-member`函数才有能力“在所有实参身上实施隐式类型转换”：

```cpp
Rational result, oneHalf;
result = oneHalf * 2;
result = 2 * oneHalf; // 编译不通过
```

本条款接着那个Rational例子来讲，把Rational class模板化：

```cpp
template<typename T>
class Rational{
public:
    Rational(const T& numerator=0,const T& denominator=1);
    const T numerator() const;
    const T denominator() const;
    ……
};
template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs) {……};
Rational<int> oneHalf(1,2);
Rational<int> result = oneHalf * 2; //错误，无法通过编译
```

在模板化后，即使把`operator*`定义为non-member，也无法完成隐式类型转换了，也就是现在`2`不能转换为`Rational<T>`了。

看一下这个例子，编译器怎么推导`T`。本例中类型参数分别是`Rational`和`int`。`operator*`的第一个参数被声明为`Rational`，传递给`operator*`的第一实参(oneHalf)正类型正是`Rational`，所以`T`一定是`int`。`operator*`的第二个参数类型被声明为`Rational`，但传递给 `operator*` 的第二个实参类型是`int`，编译器如何推算出`T`？或许你期望编译器使用Rational的non-explicit构造函数将`2`转换为`Rational`，进而推导出`T`为`int`，但它不这么做，因为在**template实参推导过程中从不将隐式类型转换考虑在内**。隐式转换在函数调用过程中的确被使用，但是在能够调用一个函数之前，首先要知道那个函数的存在；为了知道存在，必须先为相关的function template推导出参数类型（然后才可以将适当的函数具体化出来）。但是在template实参推导过程中不考虑通过构造函数发生的隐式类型转换。


现在解决编译器在`template`实参推导方面遇到的挑战，可以使用template class内的friend函数，因为template class内的friend声明式可以指涉某个特定的函数。也就是说class Rational可以说明operator* 是它的friend函数。class templates并不依赖template实参推导（后者只施行于function templates身上），所以编译器总是能够在class Rational具体化时得知T。所以令Rational class声明适当的operator*为friend函数，可以简化整个问题。

```cpp
 template<typename T>
class Rational{
public:
    friend const Rational operator*(const Rational& lhs,const Rational& rhs);//声明
};
template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,const Rational<T>& rhs) {};


Rational<int> oneHalf(1,2);
Rational<int> result = oneHalf * 2;
```
现在当我们定义`oneHalf`时，class template就已经被实例化了，同时，它的友元函数也被实列化了。


