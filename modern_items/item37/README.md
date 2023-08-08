# Item 37: 使用`std::thread`在所有路径最后都是`unjoinable`

* 在所有路径上保证`thread`最终是`unjoinable`，否则析构的时候会`std::terminate`
* 如果我们设计thread在析构时进行自动join，则会隐式的阻塞主线程，导致难以调试的问题。
* 如果我们设计trhead在析构时进行自动detach，则可能因为一些捕获的主线程栈上的对象销毁了，而发生未定义行为
* 声明数据成员时，最后声明`std::thread`对象。
