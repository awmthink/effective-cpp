# Effective-cpp

## Effective C++

* [Item 00: 导读](./items/item00/README.md)

### 1. 让自己习惯C++

* [Item 01: 视C++为一个语言联绑](./items/item01/README.md)
* [Item 02: 尽量以const、enum、inline替换#define](./items/item02/README.md)
* [Item 03: 尽可能使用const](./items/item03/README.md)
* [Item 04: 确定对象被使用前先被初始化](./items/item04/README.md)

### 2. 构造/析构/赋值运算

* [Item 05: 了解C++默默编写并调用了哪些函数](./items/item05/README.md)
* [Item 06: 若不想使用编译器自动生成的函数，就该明确拒绝](./items/item06/README.md)
* [Item 07: 为多态基类声明virtual析构函数](./items/item07/README.md)
* [Item 08: 别让异常逃离析构函数](./items/item08/README.md)
* [Item 09: 绝不在构造和析构的过程中调用virtual函数](./items/item09/README.md)
* [Item 10: 令`operator=`返回一个reference to `*this`](./items/item10/README.md)
* [Item 11: 在`operator=`中处理自我赋值](./items/item11/README.md)
* [Item 12: 复制对象时勿忘其每一个成分](./items/item12/README.md)

### 3. 资源管理

* [Item 13: 以对象管理资源](./items/item13/README.md)
* [Item 14: 在资源管理类中小心coping行为](./items/item14/README.md)
* [Item 15: 在资源管理类中提供对原始资源的访问](./items/item15/README.md)
* [Item 16: 成对使用new和delete时要采用相同的形式](./items/item16/README.md)
* [Item 17: 以独立的语句将newd对象置入智能指针](./items/item17/README.md)

### 4. 设计与声明

* [Item 18: 让接口容易被正确使用，不易被误用](./items/item18/README.md)
* [Item 19: 设计class犹如设计type](./items/item19/README.md)
* [Item 20: 宁以pass-by-reference-to-const替换pass-by-value](./items/item20/README.md)
* [Item 21: 必须返回对象，别妄想返回其reference](./items/item21/README.md)
* [Item 22: 将成员变量声明为private](./items/item22/README.md)
* [Item 23: 宁以non-member、non-friend替换member函数](./items/item23/README.md)
* [Item 24: 若所有参数皆需类型转换，请为此采用non-member函数](./items/item24/README.md)
* [Item 25: 考虑写出一个不抛异常的swap函数](./items/item25/README.md)

### 5. 实现

* [Item 26: 尽可能延后变量定义的出现时间](./items/item26/README.md)
* [Item 27: 尽可能少做转型动作](./items/item27/README.md)
* [Item 28: 避免返回handles指向对象内部成分](./items/item28/README.md)
* [Item 29: 为“异常安全”而努力是值得的](./items/item29/README.md)
* [Item 30: 透彻了解inline的里里外外](./items/item30/README.md)
* [Item 31: 将文件间的编译依赖关系降至最低](./items/item31/README.md)

### 6. 继承与面向对象设计

* [Item 32: 确定你的public继承建模出is-a关系](./items/item32/README.md)
* [Item 33: 避免hiding继承而来的名称](./items/item33/README.md)
* [Item 34: 区分接口继承和实现继承](./items/item34/README.md)
* [Item 35: 考虑virtual函数之外的其他选择](./items/item35/README.md)
* [Item 36: 绝不重新定义继承而来的non-virtual函数](./items/item36/README.md)
* [Item 37: 约不重机关报定义继承而来的缺省参数值](./items/item37/README.md)
* [Item 38: 通过复合建模出has-a或“根据某物实现出”](./items/item38/README.md)
* [Item 39: 明智而审慎地使用private继承](./items/item39/README.md)
* [Item 40: 明智而审慎地使用多重继承](./items/item40/README.md)

### 7. 模板与泛型编程

* [Item 41: 了解隐式接口和编译期多态](./items/item41/README.md)
* [Item 42: 了解typename的双重意义](./items/item42/README.md)
* [Item 43: 学习处理模板化基类内的名称](./items/item43/README.md)
* [Item 44: 将与参数无关的代码抽离templates](./items/item44/README.md)
* [Item 45: 运用成员函数模板接受所有兼容类型](./items/item45/README.md)
* [Item 46: 需要类型转换时请为模板定义非成员函数](./items/item46/README.md)
* [Item 47: 请使用traits classes表现类型信息](./items/item47/README.md)
* [Item 48: 认识template元编程](./items/item48/README.md)

### 8. 定制new和delete

* [Item 49: 了解new-handler的行为](./items/item49/README.md)
* [Item 50: 了解new和delete的合理替换时机](./items/item50/README.md)
* [Item 51: 编写new和delete时需要固守常规](./items/item51/README.md)
* [Item 52: 写了placement new也要写placement delete](./items/item52/README.md)

### 9. 杂项讨论

* [Item 53: 不要轻忽编译器的警告](./items/item53/README.md)
* [Item 54: 让自己熟悉包括TR1在内的标准程序库](./items/item54/README.md)
* [Item 55: 让自己熟悉Boost](./items/item55/README.md)


## Effective Modern C++

* [Item 00: 前言](./modern_items/item01/README.md)

### 1. 类型推导

* [Item 01: 理解模板类型推导](./modern_items/item01/README.md)
* [Item 02: 理解auto类型推导](./modern_items/item02/README.md)
* [Item 03: 理解decltype](./modern_items/item03/README.md)
* [Item 04: 学会查看类型推导的结果](./modern_items/item04/README.md)

### 2. auto类型推导

* [Item 05: 优先考虑auto而非显式类型声明](./modern_items/item05/README.md)
* [Item 06: auto推导若非己愿，使用显式类型初始化惯用法](./modern_items/item06/README.md)

### 3. 移步现代C++

* [Item 07: 区别使用`()`和`{}`创建对象](./modern_items/item07/README.md)
* [Item 08: 优先考虑nullptr而非0和NULL](./modern_items/item08/README.md)
* [Item 09: 优先考虑using而非typedef](./modern_items/item09/README.md)
* [Item 10: 优先考虑限制域enum，而非未限域enum](./modern_items/item10/README.md)
* [Item 11: 优先考虑使用deleted函数而非使用未定义的私有声明](./modern_items/item11/README.md)
* [Item 12: 使用override声明重写函数](./modern_items/item12/README.md)
* [Item 13: 优先考虑const_iterator而非iterator](./modern_items/item13/README.md)
* [Item 14: 如果函数不抛出异常请使用noexcept](./modern_items/item14/README.md)
* [Item 15: 尽可能使用`constexpr`](./modern_items/item15/README.md)
* [Item 16: 让const成员函数线程安全](./modern_items/item16/README.md)
* [Item 17: 理解特殊成员函数的生成](./modern_items/item17/README.md)

### 4. 智能指针

* [Item 18: 对独占资源使用std::unique_ptr](./modern_items/item18/README.md)
* [Item 19: 对共享资源使用std:shared_ptr](./modern_items/item19/README.md)
* [Item 20: 当std::shared_ptr可能悬空时使用std::weak_ptr](./modern_items/item20/README.md)
* [Item 21: 优化考虑使用make_unique和make_shared，而非直接使用new](./modern_items/item21/README.md)
* [Item 22: 当使用Pimpl惯用法，请在实现文件中定义特殊成员函数](./modern_items/item22/README.md)


### 5. 右值引用、移动语义与完美转发

* [Item 23: 理解std::move和std::forward](./modern_items/item23/README.md)
* [Item 24: 区分通用引用和右值引用](./modern_items/item24/README.md)
* [Item 25: 对右值引用使用std::move，对通用引用使用std::forward](./modern_items/item25/README.md)
* [Item 26: 避免在能用引用上重载](./modern_items/item26/README.md)
* [Item 27: 熟悉通用引用重载的替代方法](./modern_items/item27/README.md)
* [Item 28: 理解引用折叠](./modern_items/item28/README.md)
* [Item 29: 假定移动操作不存在，成本高，未被使用](./modern_items/item29/README.md)
* [Item 30: 熟悉完美转发失败的情况](./modern_items/item30/README.md)

### 6. Lambda表达式

* [Item 31: 避免使用默认捕获模式](./modern_items/item31/README.md)
* [Item 32: 使用初始化捕获来移动对象到闭包中](./modern_items/item32/README.md)
* [Item 33: 对于auto&&形参使用decltype以std::forward它们](./modern_items/item33/README.md)
* [Item 34: 考虑使用lambda而非std::bind](./modern_items/item34/README.md)

### 7. 并发API

* [Item 35: 优先考虑基于任务的编程而非基于线程的编程](./modern_items/item35/README.md)
* [Item 36: 如果有异步的必要请指定std::launch::async](./modern_items/item36/README.md)
* [Item 37: 从各个方面使得std::threads unjoinable](./modern_items/item37/README.md)
* [Item 38: 关注不同线程句柄析构行为](./modern_items/item38/README.md)
* [Item 39: 考虑对于单次事件通信使用void](./modern_items/item39/README.md)
* [Item 40: 对于并发使用std::atomic，volatile用于特殊内存区](./modern_items/item40/README.md)


### 8. 微调

* [Item 41: 对于那些可移动总是被拷贝的形参使用传值方式](./modern_items/item41/README.md)
* [Item 42: 考虑就地创建而非插入](./modern_items/item42/README.md)