# Item 4 学会查看类型推导结果

- 类型推断可以从IDE看出，从编译器报错看出，从Boost TypeIndex库的使⽤看出
- 这些⼯具可能既不准确也⽆帮助，所以理解C++类型推导规则才是最重要的


```cpp
#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

template <typename T>
constexpr auto GetTypeName() {
  // gcc环境下的为：constexpr auto GetTypeName() [with T = const int &]
  // msvc环境下的为：auto GetTypeName() [T = const int &]
  constexpr auto prefix = std::string_view{"T = "};
  constexpr auto suffix = "]";
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};

  const auto start = function.find(prefix) + prefix.size();
  const auto end = function.find_last_of(suffix);
  const auto size = end - start;

  return function.substr(start, size);
}
```