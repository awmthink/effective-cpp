# Item 9 优先考虑using而非typedef

- typedef 不⽀持模板化，但是别名声明⽀持。
- 别名模板避免了使⽤“ ::type ”后缀，⽽且在模板中使⽤ typedef 还需要在前⾯加上typename
- C++14提供了C++11所有type traits转换的别名声明版本
