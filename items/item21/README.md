# Item 21: 必须返回对象，别妄想返回其reference

* 绝不要返回一个指向函数内local stack的对象的引用或指针，或返回reference指向一个heap-alloacted对象，或返回pointer或reference指向一个local static对象，又有可能同时需要多个这样的对象。

我们来考虑一个有理数的类以及为它定义一个有理数想乘的友元：

```cpp
class Rational{
public:
    Rational(int numerator = 0, int denominator = 1);
private:
    int n, d;
    friend const Rational operator*(const Rational& lhs, const Rational& rhs);
}
```
现在我们来设计这个友元函数，它的功能是返回两个Rational对象的乘积，我们有3种方案：

```cpp
// 方案一
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
    Rational result(lhs.n*rhs.n, lhs.d*rhs.d);
    return result;
}
```
这个函数返回了result的引用，但是result是一个local对象，调用函数结束时，该对象会被销毁，而它的引用也就毫无意义指向了未定义的对象。

```cpp
// 方案二
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
    Rational* result=new Rational(lhs.n*rhs.n, lhs.d*rhs.d);
    return *result;
}
```

方案中result并不是一个local对象，而是一个从heap中动态分配得到的对象的指针，那么这样的问题是谁来负责delete这个指针呢，假如有这样的表达式：

```cpp
Rational w, x, y, z;
w = x * y * z;
```

这面的表达式其实调用了两次`operator*`操作，也就是创建了两次动态内存区域，但是没有办法取得它们的指针，因为表达式运算产生了中间结果，我们没有办法取得这些中间结果。

```cpp
// 方案三
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
    static Rational result;
    result = Rational(lhs.n*rhs.n, lhs.d*rhs.d);
    return result;
}
```

这次是通过static对象使得result脱离函数后依然存在，但是就像所有的static对象设计一样，这一个也立刻造成我们对多线程安全性的疑虑。而且如果有下面的代码：

```cpp
bool operator==(const Rational& lhs, const Rational& rhs);
Rational a, b, c, d;
if ((a*b) == (c*d)) {
} else {
}
```
上面代码里的`if`后的条件总是成立的，因为`a*b`返回的一个static对象的引用，而`c*d`返回的是同一个`static`对象的引用，所以永远相等。可能还会有一些大聪明想既然一个static对象不够，在同时调用时会有线程安全问题，那能不能搞成一个数组呢？那数组该取多大呢？对数组中已经存在的对象进行替换时，又会产生很大的开销。

所以，我们最终的选择是通过pass-by-value来返回新的对象。

```cpp
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.n*rhs.n, lhs.d*rhs.d);
}
```

实际上这面这种return by value，编译器是可以直接优化（RVO）的，不会产生中间的临时对象。