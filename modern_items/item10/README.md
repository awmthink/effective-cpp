# Item 10 优先考虑限制域enum，而非未限域enum

- C++98的 enum 即⾮限域 enum 。
- 限域 enum 的枚举名仅在 enum 内可⻅。要转换为其它类型只能使⽤cast。⾮限域/限域 enum 都⽀持底层类型说明语法，限域 enum 底层类型默认是 int 。⾮限域 enum没有默认底层类型。
- 限域 enum 总是可以前置声明。⾮限域 enum 仅当指定它们的底层类型时才能前置。
