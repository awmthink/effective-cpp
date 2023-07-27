# Item 10: 令`operator=`返回一个reference to `*this` 

* 令赋值（assignment）操作符返回一个reference to `*this`

核心就是使得自定义的类如同内置类型以及标准库中提供的vector, string, shared_ptr一样，可以返回一个对象自身的引用，这样可以连续赋值。

```cpp
x = y = z = 1; // 等价于：
x = (y = (z = 1));

// main.cc
// (w2=w1)表达式是一个左值
(w2 = w1).Value();
```

注意，这只是一个协议，并无强制性。如果不遵循它，代码一样可以编译。