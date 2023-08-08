# Item 2 理解auto类型推导

- auto 类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list ，⽽模板类型推导不这样做
- 在C++14中 `auto` 允许出现在函数返回值或者lambda函数形参中，但是它的⼯作机制是模板类型推导那⼀套⽅案，⽽不是 auto 类型推导

```cpp
auto x = {1, 2, 3}; // x的类型是std::initializer_list<int>

template<typename T>
void f(T param);

f({11, 23, 9}); // 错误！不能推导出T


template<typename T>
void f(std::initializer_list<T> param);
f({11, 23, 9}); // OK, T被推导为int


auto createInitList() {
    return {1, 2, 3};   // 错误，不能推导{1, 2, 3}的类型
}

auto f = [](const auto & value) { return value; };

f({1, 2, 3}); // 错误，不能推导{1, 2, 3}的类型

```