# Item 16: 成对使用new和delete时要采用相同的形式

* 如果你在new表达式中使用`[]`，必须在相应的delete表达式中也使用`[]`，如果你在new表达式中不使用`[]`，一定不要在相应的delete表达式中使用`[]`。

new表达式背后分为2步，先分配内存，再调用对象的构造函数，如果分配的数组，则会调用多次构造函数，对于delete表达式也一样，会先析构对象，再销毁内存。那么对于分配的数组，delete时一定需要知道要析构掉多少个对象，所以分配的内存中需要额外记录这个数组大小。

如果new表达式中使用`[]`，而delete表达式中没有使用`[]`，则会导致未定义的行为，因为尝试将那块内存的前面的几个字节解释为对象，调用析构函数就发生错误，而如果new表达式中没有使用`[]`，而delete表达式中使用`[]`，则可能导致，delete会读取若干的内存并将它解释为“数组大小”，然后开始多次调用析构函数。


```cpp
auto *pw = new Widget[3];
delete pw;
```
上面代码的执行结果如下：

```
Widget Ctor
Widget Ctor
Widget Ctor
Widget Dtor
munmap_chunk(): invalid pointer
Aborted (core dumped)
```

```cpp
auto *pw = new Widget;
delete[] pw;
```
上面代码的执行结果如下：

```
Widget Ctor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
Widget Dtor
free(): invalid pointer
Aborted (core dumped)
```

对于typedef过的别名，更需要注意这类问题，因为你不知道这个别名。为了避免这样问题，最好不要对数组形式做typedefs动作。