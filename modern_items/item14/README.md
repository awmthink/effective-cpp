# Item 14 如果函数不抛出异常请使用noexcept

- noexcept 是函数接⼝的⼀部分，这意味着调⽤者可能会依赖它
- noexcept 函数较之于non- noexcept 函数更容易优化
- noexcept 对于移动语义， swap ，内存释放函数和析构函数⾮常有⽤
- ⼤多数函数是异常中⽴的（译注：可能抛也可能不抛异常）⽽不是 noexcept
