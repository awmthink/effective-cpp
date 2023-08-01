# Item 22: 当使用Pimpl惯用法，请在实现文件中定义特殊成员函数。

- Pimpl惯⽤法通过减少在类实现和类使⽤者之间的编译依赖来减少编译时间。
- 对于 std::unique_ptr 类型的 pImpl 指针，需要在头⽂件的类⾥声明特殊的成员函数，但是在实现⽂件⾥⾯来实现他们。即使是编译器⾃动⽣成的代码可以⼯作，也要这么做。
- 以上的建议只适⽤于 std::unique_ptr ，不适⽤于 std::shared_ptr 。