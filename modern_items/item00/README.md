# Effective Modern C++ 前言

本书主要是教你如何利用C++11/14的一些新特性来写出正确、高效、可维护、可移植的程序。本书不是介绍C++11/14的特性，而是介绍这些特性的应用。

通过本书可以了解到以下的重要内容：

* 什么时候该用（或者不该用）auto声明
* 为什么const成员函数应当线程安全
* 怎样使用unique_ptr实现Pimpl惯用法
* 为何可避免lambda表达式用默认捕获模式
* std::atomic与volatile的区别是什么

这些内容都在本书里，本书的条款是指导方针，而不是规则，指导方针会有例外。

一些术语的约定：

* 在函数调用中，调用方传入的表达式称为函数的实参（argument）。实参被用于初始化的函数的形参（parameter）
* 通过lambda表达式创建的函数对象称为闭包。
* 产生函数的模板称为函数模板，而由模板实例化得到的函数称为模板函数。
* 产生类的模板称为类模板，由类模板实例化得到的类称为模板类。
* 声明（declarations）引入了名字和类型。而定义（definitions）提供存储位置或者实现细节。
* 函数签名是函数声明的一部分，指定了形参类型和返回类型。而函数名和形参名不是签名的一部分。
* 一个操作的结果是未定义的行为（undefined behavior）意味着运行时表现是不可预测的，比如std::vector索引下标越界，解引用未初始化的迭代器，多线程读写同一对象。