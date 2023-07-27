# Item 09: 绝不在构造和析构的过程中调用virtual函数

* 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class

在derived class对象的base class构造期间，对象的类型是base class而不是derived class。不只virtual函数会被编译器解析至（resolve to）base class，若使用运行期类型信息（RTII），也会把对象视为base class类型。