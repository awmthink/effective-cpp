# Item 01：视C++为一个语言联绑


现代的C++语言早已经不再是最早的C with class的语言了，它扩展了异常、模板、STL等新的特性。今天的C++是一个多重范型（multiparadigm）的编程语言。同时支持过程（procedural）式、面向对象（object-oriented）形式、函数（functional）形式、泛型（generic）形式、元编程（metaprogramming）形式。这些能力和弹性使得C++成为一个无可匹敌的工具，但也可能引发某些迷惑：所有“适当用法”似乎都有例外。

理解C++最简单的方法是将C++视为一个由相关语言组成的联邦，而非单一语言。在其某个次语言（sublanguage）中，各种守则与惯例都倾向简单、直观易懂、并且容易记住。然而当你从一个次语言移往另一个次语言，守则可能改变。C++的主要次语言有：

1. C。C++是以C为基础，语句块、语句、预处理器、内置数据类型、数组、指针等都来自C语言。
2. Object-Oriented C++。类的构造与析构、封装、继承、多态、虚函数等。这些都是面向对象设计中的古典概念在C++中的实现。
3. Template C++。大多数程序员对这块的经验都较少，目前Template的相关考虑与设计已经弥漫整个C++，Template威力强大。
4. STL。它对容器、迭代器、算法以及函数对象的规约有极佳的紧密配合与协调。STL有自己的一套设计原则。

基于以上4个次语言，当你从某个次语言切换到另一个，导致一些最佳实践守则的改变。比如对内置类型，我们一般是pass-by-value，但如果到了Object-Oriented C++中，对于用户自定义的对象，往往pass-by-reference可能会更好。而到了Template C++中，由于类型T是未知的，所以更难有一条确定的信条。而到了STL中，对于迭代器对象的传递，可能又会推荐使用pass-by-value的形式。

因此，C++并不是一个带有一组守则的一体语言：它是四个次语言组成的联邦，每个次语言都有自己的规约。