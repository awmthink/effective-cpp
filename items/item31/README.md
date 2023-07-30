# Item 31: 将文件间的编译依赖关系降至最低

* 支持“编译依赖最小化”的一般构想是：依赖于声明式，不要依赖于定义式。基于此构想的两个手段是Handle classes和Interface classes
* 程序库头文件应该以“完全且仅有声明式”（full and declaration-only forms）的形式存在。这种做法不论是否涉及templates都适用。

对第二条举个例子，如果我们给出去的一个库，有一个第三方依赖，第三方依赖中有若干头文件，当用户使用我们的库时，如果把这些第三方的库的头文件隐藏掉呢？

```cpp
// mylib.h
#include <3rdparty_fwd.h>


// mylib.cc
#include "mylib.h"
#include <3rdparty/a.h>
#include <3rdparty/b.h>
#include <3rdparty/c.h>

// 3rdparty_fwd.h
class A;
class B;
class C;
```


这个问题产生是源于希望编译时影响的范围尽量小，编译效率更高，维护成本更低，这一需求。

实现这个目标首先第一个想到的就是，声明与定义的分离，用户的使用只依赖声明，而不依赖定义（也就是具体实现）。

但C++的Class的定义式却不仅仅只有接口，还有实现细目（这里指实现接口需要的私有成员）。而有时候我们需要修改的通常是接口的实现方法，而这一修改可能需要添加私有变量，但这个私有变量对用户是不应该可见的。但这一修改却放在了定义式的头文件中，从而造成了，使用这一头文件的所有代码的重新编译。

于是就有了pimpl（pointer to implementation）的方法。用pimpl把实现细节隐藏起来，在头文件中只需要一个声明就可以，而这个poniter则作为private成员变量供调用。

这里会有个有意思的地方，为什么用的是指针，而不是具体对象呢？这就要问编译器了，因为编译器在定义变量时是需要预先知道变量的空间大小的，而如果只给一个声明而没有定义的话是不知道大小的，而指针的大小是固定的，所以可以定义指针（即使只提供了一个声明）。

这样把实现细节隐藏了，那么实现方法的改变就不会引起别的部分代码的重新编译了。而且头文件中只提供了impl类的声明，而基本的实现都不会让用户看见，也增加了封装性。

结构应该如下：

```cpp
class AImpl;
class A {
public:
    ...
private:
    std::tr1::shared_ptr<AImpl> pImpl;
};
```

这一种类也叫handle class

另一种实现方法就是用带factory函数的interface class。就是把接口都写成纯虚的，实现都在子类中，通过factory函数或者是virtual构造函数来产生实例。

声明文件时这么写:

```cpp
class Person
{
public:
    static shared_ptr<Person> create(const string&, const Data&, const Adress&);

    virtual ~Person();
    virtual std::string name const = 0;
    virtual std::string birthDate() const  = 0;
    virtual std::string address() const = 0;
};
```

实现文件这么写：

```cpp
class RealPerson :public Person
{
public:
    RealPerson(...);
    virtual ~RealPerson(){}
    //...
private:
    // ...
};

std::shared_ptr<Person> Person::create(
        const std::string &name,
        const Data& birthday,
        const Adress&addr) {
    return std::shared_ptr<Person>(new RealPerson(name, birthday, addr));
}
```

以上说的为了去耦合而使用的方法不可避免地会带上一些性能上的牺牲, 在handle classes身上，成员函数必须通过implementation poiner取得对象数据，增加了一层间接性。对于Interface classes，由于每个函数都是virutal，则每次函数调用付出一个间接跳跃。作者建议是发展过程中使用以上方法，当以上方法在速度与/或大小上的影响比耦合更大时，再写成具体对象来替换以上方法。