# Item 40: 明智而审慎地使用多重继承

* 多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual继承的需要。
* virtual继承会增加大小、速度、初始化（及赋值）复杂度等等成本。如果virtual base class不带任何数据，将是最具价值性的情况。
* 多重继承的确有正当用途。其中一个情节涉及：“public继承某个Interface class” 和 “private继承某个协助实现的class”的两相组合。

多重继承带来的问题是，派生类可能从一个以上的base class继承相同的名称（如函数、typedef等等）。那会导致较多的歧义。

```cpp
class BorrowableItem {
 public:
  void checkOut(int) {}
};

class ElectronicGadget {
 private:
  bool checkOut() const {}
};

class MP3Player : public BorrowableItem, public ElectronicGadget {};


MP3Player mp;
mp.checkOut(42); // Error: MP3Player::checkOut is ambiguous

mp.BorrowableItem::checkOut(42); // OK
```

我们可以看到，即使是`checkOut`只有一个调用是合法的，但函数名称解析就出错了，并没有到可用性编译这一步。

多重继承遇到的另一个问题是“菱形继承”（或叫钻石多重继承）的问题。

```cpp
class File {};
class InputFile: public File {};
class OutputFile: public File {};

class IOFile: public InputFile, public OutputFile {};
```

问题是File中的成员有两个路径继承到IOFile中，那么如何处理呢？C++给的答案是默认复制2份。如果你不希望复制，那可以使用虚拟继承。

```cpp
class File {};
class InputFile: private File {};
class OutputFile: private File {};

class IOFile: public InputFile, public OutputFile {};
```

但这就很奇怪，Dervied class需要反向要求它的Base class要以virutal继承的方式来继承自 Base Base class。

从正确行为的观点看，public 继承应该总是 virtual。如果这是唯一规则很简单：任何时候当你使用 public 继承，请改用 virtual public 继承。但是，正确性并不是唯一观点。为避免继承得来的成员变量重复，编译器必须提供若干幕后戏法，而其后果是：使用 virtual 继承的那些 classes 所产生的对象往往比使用 non-virtual继承的兄弟们体积大，访问 virtual base classes 的成员变量时，也比访问 non-virtual base classes 的成员变量速度慢。种种细节因编译器不同而异，但基本重点很清楚:你得为 virtual 继承付出代价。

virtual继承的成本还包括其他方面。支配“virtual base classes 初始化”的规则比起 non-virtual bases 的情况远为复杂且不直观。virtual base 的初始化责任是由继承体系中的最低层(most derived) class 负责，这暗示: (1) classes 若派生自 virtual bases而需要初始化，必须认知其 virtual bases，不论那些 bases 距离多远，(2) 当一个新的 derived class 加入继承体系中，它必须承担其 virtual bases（不论直接或间接的初始化责任）。

我对 virtual base classes(亦相当于对 virtual继承)的忠告很简单。第一，非必要不使用 virtualbases。平常请使用 non-virtual继承。第二，如果你必须使用 virtual base classes，尽可能避免在其中放置数据。这么一来你就不需担心这些 classes 身上的初始化 (和赋值)所带来的诡异事情了。

下面来看一个多重继承的合理的使用：

```cpp
class IPerson {};

class PersonInfo {};

class CPerson: public IPerson, private PersonInfo {};
```

在上面的示例中：`IPerson`是一个定义的抽象接口类，`CPerson`是具体的实现类，但我们在实现`CPerson`时，发现其大部分功能可以借助`PersonInfo`来实现，那么按条款39，我们可以private继承`PersonInfo`。