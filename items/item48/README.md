# Item 48: 认识模板元编程

* Template metaprogramming (TMP 模板元编程)可将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率。
* TMP可以被用来生成“基于政策选择组合”的客户定制代码，也可用来避免生成对某些特珠类型并不适合的代码。

模板元编程（TMP）是指用C++模板相关的技术来编写执行编译期间的程序。模板元程序是以C++写成、执行于C++编译器内的程序。

C++并非是为模板元编程而设计，但1990s初期TMP被发现出来，证明还十分有用；所以TMP是发现出来的，不是发明出来的。TMP有两大特别的能力：

1. 它让某些事情更容易，如果没有它，那些事情将是困难的，甚至是不可能的；
2. 由于执行于C++编译期，因为可以将工作从运行期移到编译期。原来有些错误要到运行期才能发现，现在在编译期就可以找出来。

但TMP的程序使得代码的编译时间变长了。

TMP已被证明是“图灵完全（turning-complete）机器，意思是它的威力大到足以计算任何事物。使用TMP你可以声明变量、执行循环、编写及调用函数。这些用法和“正常的C++”对应物看起来很是不同。TMP的一个“Hello,World程序”


```cpp
template<int n>
struct Factorial {
    enum {value = n * Factorial<n-1>::value }
};

template<>
struct Factorial<0> {
    enum {value = 1 }
};

std::cout << Factorial<5>::value << std::endl; // 120
```