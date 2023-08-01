# Item 21: 优化考虑使用make_unique和make_shared，而非直接使用new

- 和直接使⽤ new 相⽐， make 函数消除了代码重复，提⾼了异常安全性。对于std::make_shared 和 std::allocate_shared ，⽣成的代码更⼩更快。
- 不适合使⽤ make 函数的情况包括需要指定⾃定义删除器和希望⽤花括号初始化。
- 对于 std::shared_ptr，其他不建议使⽤ make 函数的情况包括：(1)有⾃定义内存管理的类；(2)特别关注内存的系统，⾮常⼤的对象，以及 std::weak_ptr s⽐对应的std::shared_ptr s活得更久。
