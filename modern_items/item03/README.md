# Item 3 理解decltype

- decltype 总是不加修改的产⽣变量或者表达式的类型
- 对于 T 类型的不是单纯的变量名的左值表达式， decltype总是产出 T 的引⽤即 T& 。
- C++14⽀持 decltype(auto) ，就像 auto ⼀样，推导出类型，但是它使⽤ decltype 的规则进⾏推导。
