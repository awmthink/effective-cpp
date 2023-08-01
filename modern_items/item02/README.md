# Item 2 理解auto类型推导

- auto 类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list ，⽽模板类型推导不这样做
- 在C++14中 auto 允许出现在函数返回值或者lambda函数形参中，但是它的⼯作机制是模板类型推导那⼀套⽅案，⽽不是 auto 类型推导
