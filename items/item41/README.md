# Item 41: 了解隐式接口和编译期多态

* classes和tempaltes都支持接口和多态
* 对classes而言接口是显式的，以函数签名为中心，多态则通过virtual函数发生于运行期
* 对template参数而言，接口是隐式的，基于有效表达式。多态则是通过template的实例化和函数重载解析发生于编译期

考虑以下的函数：

```cpp
void doProcessing(Widget& w) {
    if (w.size() > 10 && w != someNastyWidget) {
        Widget temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

我们从面向对象的角度来思埏`doProcessing`的参数`w`，首先它的类型一定是`Widget`或`Widget`的派生类，其次，对于`Widget`类型，它一定有以下public的接口：

* size()成员函数，函数返回一个可以和10比大小的类型
* 存在`operator!=`运算符，右参的类型取决于someNastyWidget的类型
* 支持拷贝构造
* 存在normalize()成员函数
* 存在swap()成员函数

上面的成员函数中，有一些可以是virtual，那么这些函数在函数调用的运行期就会表现出多态。

下面我们从面向对象的世界进行泛型编程的世界：

```cpp
template<typename T>
void doProcessing(T& w) {
    if (w.size() > 10 && w != someNastyWidget) {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

在泛型编程的世界里，类型`T`没有了像`Widget`一样的显式的接口定义与约束，变成了隐式接口和编译期多态。所谓的隐式接口是指：`w`支持哪一种接口，并没有一组接口函数显式的定义出来，而是由template中执行于`w`身上的操作来决定，也就说由有效表达式（valid expression）组成。

隐式接口区别与面象对象中的显式接口，`w`只需要满足能使表达式有效就行了（包括通过各种隐式转换），不一定需要实现`Widget`中的全部接口。编译期多态表现在，模板函数中的对于`w`的接口调用，都会导致对应实例化，这些发生在编译期，也就是：“以不同的tempalte参数实例化函数模板，就会导致不同的函数”，这就是编译期多态。
