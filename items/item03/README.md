# Item 03: 尽可能使用const

* 将某些东西声明为const可帮助编译器侦测出错误的用法。const可被施加于任何作用域内的对象，函数对参数，函数返回类型，成员函数本体。
* 编译器强制实施bitwise constness，但你编写程序时应用使用“概念上的常量性”。
* 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。

**指向const对象的指针** vs **指向普通对象的const指针**：如果关键字`const`出现在星号左边，则表示指向的对象是常量；如果出现在星号右边，则表示指针自身是常量。

```cpp
void f1(const Widget *pw);
void f2(const *Widget pw);
```
上面两种形式的`pw`都是一个指向const对象的指针。

如何表示一个常量对象的迭代器：

```cpp
std::vector<int> vec;
// iter 是一个批向容器首个元素的const迭代器
// iter指向的内容可以修改，iter不能修改
const std::vector<int>::iterator iter = vec.begin();

// citer是一个const_iterator，指向的对象是const的
// 我们可以修写citer，但不能修改citer指向内容
auto citer = vec.cbegin();
```

const应用在成员函数上，有两个流行概念：**bitwise constness**和**logical constness**，编译器能够检查的是bitwise constness。bitwise const阵营的人相信，成员函数只有在不更改对象任何成员变量时才可以说是const。也就是说它不更改对象内任何一个bit。这种观点的好处是，编译非常容易侦测违反点。

**bitwise constness**的缺点是许多成员函数虽然不十足具备const性质，却能够通过bitwise测试，具体来说，一般都是改变了类中的一些指针成员指向的内容。

```cpp
class TextBook
{
public:
    char &operator[](std::size_t pos) const { return pText[pos]; }

    std::size_t length() const
    {
        if (!lengthIsValid)
        {
            textLength = std::strlen(pText);
            lengthIsValid = true;
        }
        return textLength;
    }

private:
    char *pText;
    mutable std::size_t textLength; // 缓存
    mutable bool lengthIsValid;
};
```
这个class不适当的将其operator[]声明为const成员函数，而该函数却返回一个reference指向对象内部值，这个函数是bitwise const，所以编译器不会有任何提示。

而对于`length`函数，它的实现当然不是bitwise const，但是length函数对客户端来说，实际看起来就是const的。

在一个类中，我们很多时候可能要对同一个成员函数同时提供`const`和non-const的版本，这就需要写2份代码，为了去除代码上的冗余，可以用非const版本去调用const版本。

```cpp
const char &operator[](std::size_t pos) const { return pText[pos]; }

char &operator[](std::size_t pos)
{
    return const_cast<char &>(static_cast<const TextBook &>(*this)[pos]);
}
```
注意上面的代码里有2处转型，其中`static_cast<const TextBook &>(*this)`将对象转为一个const对象，否则我们对于`opeator[]`的调用会形成递归调用，由于是non-const向const转换，所以可以直接用static_cast。

这个问题在C++23中，可以利用`Deducing this`这个特性来解决：[C++23’s Deducing this: what it is, why it is, how to use it](https://devblogs.microsoft.com/cppblog/cpp23-deducing-this/)


