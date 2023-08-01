# Item 20: 当std::shared_ptr可能悬空时使用std::weak_ptr

- ⽤ std::weak_ptr 替代可能会悬空的 std::shared_ptr 。
- std::weak_ptr 的潜在使⽤场景包括：缓存、观察者列表、打破 std::shared_ptr 环状结构。
