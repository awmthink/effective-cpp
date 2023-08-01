# Item 25: 对右值引用使用std::move，对通用引用使用std::forward

- 最后一次使用时，在右值引用上使用std::move，在通用引用上使用std::forward。
- 对按值返回的函数要返回的右值引用和通用引用，执行相同的操作。
- 如果局部对象可以被返回值优化消除，就绝不使用std::move或者std::forward。
