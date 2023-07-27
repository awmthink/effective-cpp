# 导读

## 关于本书

* 学习C++语言的语法规则是一回事；学习如何以C++语言来设计和实现高效的程序是另一回事。
* 本书的条款主要有两类：1）一般性的设计策略，比如选择继承还是选择模板，选择public继承和还是private继承，选择private继承还是选择组合，选择pass-by-value还是pass-by-refernce；2）带有具体细节的特定语言特性，比如：什么是assignment操作符的适当返回类型，何时该令析构函数为virtual。
* 本书的主要目的是要强调那些常常被漠视的C++编程方向与观点。其他书会介绍C++的各个部分，本书会告诉你如何组合那些成分以便最终获得有效的程序，其他书告诉你如何让程序通过编译，没有语法错误，本书告诉你如何回避编译器难以显露的问题。（说白了就是最佳实践，现在一个静态代码分析工具也可以给出提示。）
* 本书的条款都是一种引导，告诉我们如何发展出更好的设计，如何避免常见的问题，或是如何达到更高的效率，但没有任何一个条款放之四海皆准、一体适用。
* 软件设计和实现是复杂的事情，被硬件、操作系统、应用程序的约束条件涂上五颜六色。

## 术语

* 声明（declaration）：告诉编译器某个东西的名称和类型（type），但略去细节。

    ```cpp
    // 对象声明
    extern int x;
    // 函数声明
    std::size_t numDigits(int number);
    //类声明
    class Widget;
    // 模板类声明
    template<typename T>
    class GraphNode;
    ```
* 对象（object）：所有C++中定义的变量/常量，包括内置类型、自定义类型
* 定义（definition）：提供编译器一些声明中所遗漏的细节。对对象而言，定义则是编译器为该对象分配内存的地点。对于function或function template而言，定义则是提供代码本体，对于class或class template而言，定义则列出了它们的成员；
    ```cpp
    int x; // 对象的定义

    // 函数的定义
    std::size_t numDigits(int number) {
        std::size_t digitsSoFar = 1;
        while ((number /= 10) != 0) ++digitsSoFar;
        return digitsSoFar;
    }

    // 类的定义
    class Widget {
    public:
        Widget();
        ~Widget();
        ...
    };

    // 模板的定义
    template <typename T>
    class GraphNode {
    public:
        GraphNode();
        ~GraphNode();
        ...
    };
    ```
* 初始化（initialization）：给予对象初值的过程。对于用户定义类型的对象而言，初始化由构造函数执行。
* 未定义的行为（undefined behavior）：C++标准中没有规定，你无法稳定预估运行期会发生什么事，比如解引用无效的迭代器或指针，数组下标越界等。
* 接口（interface）：函数的签名或class的可访问元素（包括：public接口、protected接口、private接口）