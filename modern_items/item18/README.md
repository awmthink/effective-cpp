# Item 18: 对独占资源使用std::unique_ptr

- std::unique_ptr 是轻量级、快速的、只可移动（move-only）的管理专有所有权语义资源的智能指针
- 默认情况，资源销毁通过 delete 实现，但是⽀持⾃定义删除器。有状态的删除器和函数指针会增加 std::unique_ptr 对象的⼤⼩
- 将 std::unique_ptr 转化为 std::shared_ptr ⾮常简单
