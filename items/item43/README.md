# Item 43: 学习处理模板化基类内的名称

* 可在derived class templates内通过this->指涉base class templates内的成员名称，或藉由一个明白写出base class资格修饰符完成。

模板化的类作为基类时，有哪些要注意的地方。以一个例子说明，假设现在编写一个发送信息到不同公司的程序，信息要么译成密码，要么就是原始文字，在编译期间来决定哪一家公司发送至哪一家公司，采用template手法：

```cpp
    class CompanyA {
    public:
        void sendCleartext(const std::string& msg);
        void sendEncryted(const std::string& msg);
        ……
    };
    class CompanyB {
    public:
        void sendCleartext(const std::string& msg);
        void sendEncryted(const std::string& msg);
        ……
    };
    ……//还有一些公司

    class MsgInfo{……};//用来保存信息，以备将来产生信息

    template<typename Company>
    class MsgSender {
    public:
        ……//构造析构等函数
        void sendClear(const MsgInfo& info) {
            std::string msg;
            //根据info产生信息
            Company c;
            c.sendCleartext(msg);
        }
        void sendSecart(const MsgInfo& info) {……}
    };
```

上面这个做法行得通，但是如果要在每次送出信息时记录日志，可以派生出derived class，加上记录的日志：

```cpp
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>
{
public:
    ……//析构构造等
    void SendClearMsg(const MsgInfo& info)
    {
        //发送前的信息写到log
        sendClear(info);//调用base class函数，这段代码无法通过编译
        //传送后信息写到log
    }
};
```
当编译器遇到class template LoggingMsgSender定义式时，不知道它继承什么样的class，因为MsgSender中的Company是个参数，在LoggingMsgSender被具体化之前，无法确切知道它是什么，自然而然就不知道class MsgSender是什么，也就不知道它是否有个sendClear函数。

因为有可能一些Company的实现类，对MsgSender做了特化，根本就没有提供sendClear函数。

解决办法有三点：

1. 在base class调用动作之间加上`this->`：

```cpp
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    void SendClearMsg(const MsgInfo& info) {
        this->sendClear(info);
    }
};
```

2. 使用using声明式：

```cpp
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    //告诉编译器，假设sendClear位于base class内
    using MsgSender<Company>::sendClear;
    void SendClearMsg(const MsgInfo& info) {
        sendClear(info);
    }
};
```

3. 明白的告诉编译器被调用的函数位于base classes内：

```cpp
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    void SendClearMsg(const MsgInfo& info) {
        MsgSender<Company>::sendClear(info);
    }
};
```
这种做法使用了明确资格修饰符（explicit qualification），这将会关闭virtual绑定行为。




