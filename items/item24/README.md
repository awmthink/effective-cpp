# Item 24: 若所有参数皆需类型转换，请为此采用non-member函数

当我们为一个有理数类的设计一个乘法操作符的重载函数，如果我们把它作为类的成员：

```cpp
class Rational
{
public:
    //...
    const Rational operator*(const Rational &lhs);
};
```

当我们尝试混合算术的时候，你会发现只有一半行得通：

```cpp
Rational result, oneHalf;
result = oneHalf * 2;
result = 2 * oneHalf; // 编译不通过
```

上面第二个赋值语句是错误的，因为它等价于`result=2.operator*(oneHalf)`，这显然是错误的。而第2条语句等价于`result=oneHalf.operator(2)`,它可以执行成功是因为2发生了隐式类型转换，因为Rational有一个non-explicit的接受int形参的构造函数。

所以，如果我们想执行上面的操作，我们需要将这个重载函数设计为non-member函数。

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs);
```

本条款内含真理，但却不是全部的真理。当你从 Object-Oriented C++ 跨进Template C++，并让 Rational 成为一个 class template 而非 class，又有一些需要考虑的新争议、新解法、以及一些令人惊讶的设计牵连。这些争议、解法和设计牵连形成了[条款 46](../item46/README.md)。