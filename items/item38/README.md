# Item38: 通过复合建模出has-a或“根据某物实现出”

* 复合的意义和public继承完全不同。
* 在应用领域，复合意味着 has-a。在实现领域，复合意味着 is-implemented-in-terms-of

条款 32 曾说，“public 继承”带有 is-a(是一种)的意义。复合也有它自己的意义。实际上它有两个意义。复合意味 has-a(有一个)或is-implemented-in-terms-of(根据某物实现出)。

为什么它有两个意义呢？那是因为你正打算在你的软件中处理两个不同的领域(domains)。程序中的对象其实相当于你所塑造的世界中的某些事物，例如人、汽车、一张张视频画面等等。这样的对象属于**应用域 (application domain)**部分。其他对象则纯粹是实现细节上的人工制品，像是缓冲区(buffers)、互斥器(mutexes)、查找树(search trees)等等。这些对象相当于你的**软件的实现域(implementation domain)**。当复合发生于应用域内的对象之间，表现出 has-a 的关系；当它发生于实现域内则是表现 is-implemented-in-terms-of 的关系。

```cpp
class Address {}; // 表示某人的地址
class PhoneNumber {}; // 表示某人的手机号

class Person {
private:
    std::string name;
    Address address;
    PhoneNumber voiceNumber;
    PhoneNumber faxNumber;
};
```

Peson对象是由string、Address、PhoneNumber等构成，我们称为复合（composition）或包含。它表示一种has-a关系，Person有一个名字、有一个地址、有一个语音和传真号码。

现在如果我们想实现一个集合，但是用`std::set`的话，空间开销太大，因为每个元素额外使用3个指针。我们可以考虑直接用`std::vector`来实现，因为我们并不在乎查找的效率。

```cpp
template<typename T>
class MySet: public std::vector<T> {};
```
这显然不是一个好的选择，因为MySet并不一种std::vector，不是has-a的关系，std::vector允许元素重复，但MySet显然不满足。合理的做法就是使用复合：

```cpp
template<typename T>
class MySet {
private:
    std::vector<T> rep; // 用于存储set中的数据
};
```