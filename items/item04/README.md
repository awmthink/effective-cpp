# Item 04: 确定对象被使用前先被初始化

* 为内置型对象手工初始化，因为C++不保证初始化它们。
* 构造函数最好使用成员初始列（member initialization list），而不要在构造函数本体内使用赋值操作（assignment）。初始列列出的成员变量，其排列次序应该和它们的在class中的声明次序相同。
* 为了避免跨编译单元初始化次序的问题，请以local static对象替换non-local static对象。

C++规定对于类的成员变量，它们的初始化动作发生在进入构造函数本体之前，在构造函数中写的赋值语句实际上都是拷贝复制。强烈推荐对于类成员的初始化构造都写在初始化构造列表中，而且一些const成员，引用成员也必须在成员初始列中进行初始化。

```cpp
class Widget
{
    Widget(int sz) : size(sz), pArray(new int[size]) {}

private:
    int *pArray;
    int size;
};
```
上面这个代码实际上是有问题的，虽然在构造函数的成员初始列中，看起来size是先初始化的，但真实的初始化顺序是按成员在类中定义的顺序，所以在为pArray分配内存时，size的值是未初始化的状态。


一个non-local static对象是指在函数外部定义的静态变量。它不是在函数内部定义的局部变量，而是在整个程序的生命周期内都存在。这种对象可以在程序启动时初始化，并在程序结束时销毁，它的作用域是全局的，可以被整个程序的任何部分访问。全局变量也是一种non-local static对象。它们在程序启动时被初始化，在程序结束时被销毁，其作用域也是全局的。

non-local static对象一般存储在程序的静态存储区中。静态存储区是程序运行时分配的一块内存空间，用于存储全局变量、静态变量、常量等在程序运行期间始终存在的数据。它的生命周期与程序的生命周期相同，因此在程序启动时，静态存储区就被分配出来了，其中的non-local static对象也在此时被初始化。由于non-local static对象是在全局作用域中定义的，所以它们可以被整个程序的代码访问。

基于上面介绍，当两个编译单元中定义了2个不同的non-local static对象时，它们的初始化顺序是没有保证的，所以它们彼此之间不要有任何依赖关系。解决这类问题，需要要把对应的对象搬到函数内，变为local static对象，C++保证，函数内的local static对象会在该函数被调用期间，首次遇上该对象定义时进行初始化。

```cpp
class Widget {};

Widget& GetWidget() {
    static Widget w;
    return w;
}
```