# Item 30: 透彻了解inline的里里外外

* 将大多数inline限制在小型、被频繁调用的函数上。这可使日后的调试过程和二进制升级（binary upgradability）更容易，也可以使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化。
* 不要因为function templates出现在头文件中，就将它们声明为inline。

inline函数免除函数调用的成本只是优化的一部分，编译器通常会对不包含函数调用的代码设计特别的优化。

但inline函数的展开可能会导致代码膨胀，这可能会导致指令加载时额外的换页行为，降低高速缓存的命中率（instruction cache hit rate）。

有些隐藏的inline的场景：将函数定义在class定义内，比如成员函数或友元函数。另外就是一些显式的inline的函数；但并不是显式加了inline的函数就会真的变成内联的，大部分编译器拒绝将太过复杂的函数内联，比如包括了递归或循环。而且所有virtual函数的调用都不会被内联，因为对于virutal函数的调用，编译器不知道该调用哪个函数，这个只有在运行时才知道。

如果程序要取某个inline函数的地址，编译器通常必须为此函数生成一个outlined函数本体。另外，如果使用函数指针来进行函数调用，则这个调用也不会被内联。

```cpp
inline void f() {}
void (*pf) () = f;

f();    // 可以内联
fp();   // 不被内联
```

对构造函数和析构函数内联往往也不是一个好主意，尤其是对于派生类的构造与析构函数，因为它们实际编译器生成的代码往往比你看到实现本体里代码多很多。这就会导致很严重的代码膨胀。

最后2条inline的缺点：1）如果我们的函数是以库的形式给出，内联会导致我们后续的库升级很麻烦，客户端必须重新编译；2）inline函数对调试器来说是灾难，一般在debug时会拒绝所有inline。


