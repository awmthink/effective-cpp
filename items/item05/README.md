# Item 05: 了解C++默默编写并调用了哪些函数

* 编译器可以暗自为class创建default构造函数、copy构造函数、copy assignment操作符、以及析构函数。

一个空的类，编译器会为它声明：

* 默认构造函数
* copy构造函数
* move构造函数
* copy assignment操作符
* move assignment操作符
* 析构函数

只有当这些函数被需求（被调用），它们才会被编译创建出来。对于copy assignment操作符来说，如果类中有const或引用成员，则不会合成copy assignment操作符。