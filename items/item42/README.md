# Item 42: 了解typename的双重意义

* 声明tempalte参数时前缀关键点class和typename可以互换
* 请使用关键点typename标识嵌套从属名称；但不得在base class list（基类列表）和member initialization list（成员初值列）内以它作为base class修饰符。

```cpp
template<typename C>
void print2nd(const C& container) {
    if (container.size() < 2) {
        return;
    }
    typename C::const_iterator iter(container.begin());
    ++iter;
    std::cout << *iter << std::endl;
}
```
由于`const_iterator`的类型是依赖于模板参数`C`的，因为它可能不是一种类型，可能是`static成员`。如果我们的表达式是：`C::const_iterator* x`，那么当`const_iterator`是一个static成员时，这就是一个乘法运算表达式。

```cpp
template<typename T>
class Derived: public Base<T>::Nested {
public:
    explicit Derived(int x): Base<T>::Nested(x) {
        typename Base<T>::Nested temp;
        ...
    }
};
```
如上，在base class list（基类列表）和member initialization list（成员初值列）内的从属类型（Nested）是不需要加`typename`的。