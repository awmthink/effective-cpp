# Item 17: 以独立的语句将newd对象置入智能指针

* 以独立的语句将newd对象置入智能指针。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。



```cpp
int priority();
void processWidget(std::shared_ptr<Widget> pw, int priority);

processWidget(std::shared_ptr<Widget>(new Widget), priority());
```

对于processWidget的调用，编译器必须创建代码，做下面三件事：

1. 调用priority()函数
2. 执行new Widget
3. 调用shared_ptr的构造函数

C++编译器以什么样的顺序来完成上面3件事是没有保证的，很有可能的调用顺序是：

1. 执行new Widget
2. 调用priority()函数
3. 调用shared_ptr的构造函数

如果priority()函数抛出了异常，则`new Widget`申请出来的内存就发生了泄漏。所以建议改为2条语句：

```cpp
auto pw = std::make_shared<Widget>();
processWidget(pw, priority());
```