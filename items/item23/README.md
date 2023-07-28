# Item 23: 宁以non-member、non-friend替换member函数

* 宁可拿non-member non-friend函数替换member函数。这样做可以增加封装性、包裹弹性和机能扩充性。

想像有个class用来表示网页浏览器。这样的class可能提供的众多函数中，有一个用来清除下载元素的高速缓冲区(cache of downloaded elements)、清除访问过的URLs的历史记录、以及移除系统中所有的cookies。

```cpp
class WebBrowse
{
public:
    void clearCache();
    void clearHistroy();
    void removeCookies();
};
```

许多用户想一个函数来执行整个动作，因些WebBrowse也提供这样一个函数：

```cpp
class WebBrowse
{
public:
    //...
    void clearEverything();//依次调用clearCache(),clearHistory(),removeCookies()
};
```

当然这个功能也可以由一个non-member函数来完成：

```cpp
void clearEverything(WebBrowse& wb)
{
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}
```

根据面向对象守则要求，数据以及操作的那些函数应该捆绑在一块，这意味着member函数是较好的选择。不幸的是这个建议不正确。这是基于对面向对象真实意义的一个误解，面向对象要求数据应该尽可能被封装。

让我们从封装开始讨论。如果某些东西被封装，它就不再可见。愈多东西被封装,愈少人可以看到它。而愈少人看到它，我们就有愈大的弹性去变化它，因为我们的改变仅仅直接影响看到改变的那些人、事、物。因此，愈多东西被封装，我们改变那些东西的能力也就愈大。这就是我们首先推崇封装的原因:它使我们能够改变事物而只影响有限客户。

现在考虑对象内的数据。愈少代码可以看到数据(也就是访问它)，愈多的数据可被封装，而我们也就愈能自由地改变对象数据，例如改变成员变量的数量、类型等等。如何量测“有多少代码可以看到某一块数据”呢?我们计算能够访问该数据的函数数量，作为一种粗糙的量测。愈多函数可访问它，数据的封装性就愈低。

member函数带来的封装性比non-member函数低，因为member函数增加了“能够访问class内之private成份”的函数数量。

此外，提供non-member函数可以允许对WebBrowse相关机能能有较大的包裹弹性，而那最终导致较低的编译相依度，增加WebBrowse的可延伸性。如果我们把WebBrowse相关的功能设计为non-member函数，那么可以将其功能相关的函数的声明单独放在一个头文件中，然后在一个命名空间下。这时候如果我们相扩展相关的这些功能，只需要像其他功能函数一样把声明入在头文件里即可。