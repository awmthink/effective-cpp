# Item 36: 如果有异步的必要请指定`std::launch::async`

* `std::async`的默认启动策略是异步和同步执行兼有的。
* 这个灵活性导致访问`thread_local`的不确定性，隐含了任务可能不会被执行的意思，会影响调用基于超时的`wait`的程序逻辑。
* 如果异步执行任务非常关键，则指定`std::launch::async`。
