# Item 12: 复制对象时勿忘其每一个成分

* Copying函数应该确保复制“对象内的所有成员变量”以及“所有base class成分”。
* 不要尝试以某个copying函数实现另一个copying函数。应该将共同机能放进第三个函数中，并由两个copy函数共同调用。

针对第2点，应该也是可以互相调用的：

```cpp
Customer(const Customer &rhs) { 
  *this = rhs;
}

Customer &operator=(const Customer &rhs) {
  new (this) Customer(rhs);
  return *this;
}
```


值得注意的是在拷贝构造函数中调用赋值运算符`*this = rhs`是不合适的，因为这样做会导致对象被创建后又被销毁，然后再被重新赋值，从而浪费了运行时间和空间资源。

其次，在赋值运算符中使用了`placement new`运算符，即`new (this) Customer(rhs)`。这个运算符可以在已经分配的内存地址上构造一个新的对象，但它并不会调用析构函数，因此会导致内存泄漏。正确的实现方式应该是先调用析构函数，再重新构造对象。