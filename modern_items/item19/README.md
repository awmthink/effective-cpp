# Item 19: 对共享资源使用std:shared_ptr

- std::shared_ptr 为有共享所有权的任意资源提供⼀种⾃动垃圾回收的便捷⽅式。
- 较之于 std::unique_ptr ， std::shared_ptr 对象通常⼤两倍，控制块会产⽣开销，需要原⼦性的引⽤计数修改操作。
- 默认资源销毁是通过 delete ，但是也⽀持⾃定义删除器。删除器的类型是什么对于std::shared_ptr 的类型没有影响。
- 避免从原始指针变量上创建 std::shared_ptr 。
