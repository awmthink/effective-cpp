# Item 15: 在资源管理类中提供对原始资源的访问

* APIs往往要求访问原始资源（raw resources），所以每一个RAII class应该提供一个“取得其所管理的资源”的办法。
* 对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。

很多底层的APIs，尤其是一个偏C风格的APIs，它们都是使用原始的资源，比如指针、文件句柄，线程句柄等。

几乎所有的智能指针，都提供了`.get()`接口用于获取内部的实际指针，这就是显式的转换。同时智能指针也重载了`operator->`和`operator*`这样的运算符，使得它可以隐式的看起来像使用指针一样。

你可能会觉得提供像`.get()`这样的接口，与“封装”发生矛盾，但RAII class并不是为了封装某物而存在的。