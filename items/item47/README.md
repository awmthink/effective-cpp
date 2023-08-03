# 条款47：请使用traits class表现类型信息

* 建立一组重载函数或函数模板（例如doAdvance），彼此间差异只在于各自的traits参数。每个函数实现与之接受的traits信息像匹配。
* 建立一个控制函数或函数模板（例如advance），调用上面的函数并传递traits class信息。

考虑如何给STL中的迭代器实现一个移动一定距离的函数：

```cpp
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d); // d大于零，向前移动，小于零则向后移动
```

表面上看，只是`iterate+=d`的动作，但是迭代器有5中，只有random access（随机访问）迭代器才支持`+=`操作。其他类型没这么大威力，只有反复`++`和`–-`才行。

在了解了迭代器类型后，我们该去实现advance函数了。实现要高效，对于random access迭代器来说，前进d距离要一步完成，而其他类型则需要反复前进或后退：

```cpp
template<typename Iter, typename DistT>
void advance(IteT& iter, DistT d)
{
    if(iter is a random access iterator)
        iter += d;
    else {
        if(d>=0)
            while(d--) ++iter;
        else 
            while(d++) --iter;
    }
}
```

这里有2个问题，一个是如果拿到一个迭代器所属于的类型，另一个是我们无法使用运行态的`if-else`来进行编译期的判断。

第一个问题的直接的解决办法是：STL中所有容器的迭代器，都有一个`iterator_category`的`typedef`。我们使用这个类型信息就可以了。但面临的问题是，在C++中原生指针也是一种迭代器。但指针并没有`iterator_category`这样的`typedef`。这时候traits技术就出现了。

Traits 并不是 C++ 关键字或一个预先定义好的构件；它们是一种技术，也是个 C++ 程序员共同遵守的协议。这个技术的要求之一是，它对内置 (built-in)类型和用户自定义(user-defined)类型的表现必须一样好。举个例子，如果上述 advance收到的实参是一个指针(例如 const char*)和一个 int，上述 advance 仍然必须有效运作，那意味 traits 技术必须也能够施行于内置类型如指针身上。

traits 必须能够施行于内置类型意味“类型内的嵌套信息，也就是类中typedef”这种东西出局了，因为我们无法将信息嵌套于原始指针内。因此类型的 traits 信息必须位于类型自身之外。标准技术是把它放进一个 template 及其一或多个特化版本中。这样的 templates 在标准程序库中有若干个，其中针对迭代器者被命名为 iterator traits:

```cpp
// 针对STL中容器提供的迭代器版本
template<typename IterT>
struct iterator_traits {
    typedef typename IterT::iterator_category iterator_category;
};

// 针对指针的版本特化
template<typename IterT>
struct iterator_traits<IterT*> {
    typedef random_access iterator_tag iterator_category;
};
```

最后我们来看，如何解决编译期如何进行`if-else`的问题，我们可以通过函数重载，不同的参数重载不同的函数实现：

```cpp
template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::random_access_iterator_tag)
{
    iter+=d;
}

template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::bidirectional_iterator_tag)
{
    if(d>=0)
        while(d--) ++iter;
    else 
        while(d++) --iter;
}

template<typename IterT, typename DisT>
void doAdvance(IterT& iter, Dist d, std::input_iterator_tag)
{
    if(d<0)
        throw std::out_of_range("Negative distance");
    while(d++) --iter;
}

template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d)
{
    doAdvance(iter, d, typename::std::iterator_traits<IterT>::iterator_category());
}
```