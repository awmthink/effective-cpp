# Item 06: 若不想使用编译器自动生成的函数，就该明确拒绝

* 为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private并且不予实现。使用像Uncopyable这样的base class也是一种做法。

有些类构造出来后就是独一无二的，我们不希望在它们身上进行复制，如何阻止编译器自动生成的copy构造函数和copy assignment操作符呢？

1. 声明为private的，而且不定义，即使是member成员尝试使用它们，会获得一个链接错误（linkage error）。
2. 将错误由链接期转移到编译期：继承一个Uncopyable的基类。

    ```cpp
    class Uncopyable {
    protected:
      Uncopyable() = default;
      ~Uncopyable() = default;

    private:
      Uncopyable(const Uncopyable&);
      Uncopyable& operator=(const Uncopyable&);
    };

    // 由于Widget内的base class不可copy构造和copy assignment
    // 所以编译将Widget的copy构造和copy assignment标记为delete
    class Widget : private Uncopyable {};
    ```
3. 在C++11以后直接使用`=delete`。