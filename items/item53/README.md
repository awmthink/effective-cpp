# Item 53: 不要轻忽编译器的警告

* 严肃对待编译器发出的警告信息，努力在你的编译器的最高的警告级别下争取“无任何警告”的荣誉。
* 不要过度依赖编译器的报警能力，因为不同的编译器对待事情的态度并不相同。一旦移植到了另一个编译器上，你原来倚赖的警告信息有可能消失。

我们可以选择忽略编译器警告，但前提是让这些警告都显式的报出来，然后我们能够了解对应的警告的精确意义。