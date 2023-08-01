# Item 34: 考虑使用lambda而非std::bind

- 与使用std::bind相比，lambda更易读，更具表达力并且可能更高效。
- 只有在C++11中，std::bind可能对实现移动捕获或绑定带有模板化函数调用运算符的对象时会很有用。
