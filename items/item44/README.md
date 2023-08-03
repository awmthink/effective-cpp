# Item 44: 将与参数无关的代码抽离templates

* Template生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系
* 因为非类型模型参数而造成的代码膨胀，往往可以消除，做法是以函数参数或class成员变量替换template参数。
* 因为类型参数而造成的膨胀，往往可以降低，做法是让带有完全相同二进制表达的实例化类型共享实现代码。

本Item的核心需求是如何避免模板代码的膨胀。

使用模板也避免代码重复这个事情我们都知道，但如果我们不小心，也可以会因为模板大量的实例化，导致程序编译后的二进制代码膨胀。可能源码看起来很整齐，但目标码可能很肥胖。

先来学习一个名词：共性与变性分析（commonality and variability analysis）。比较容易理解。例如，你在编写几个函数，会用到相同作用的代码；这时候你往往将相同代码搬到一个新函数中，给其他几个函数调用。同理，如果编写某个class，其中某些部分和另外几个class相同，这时候你不会重复编写这些相同部分，只需把共同部分搬到新class中去即可，去使用继承或复合，让原先的classes取用这些共同特性，原classes的互异部分（变异部分）仍然留在原位置不动。

下面的示例演示了我们为一个固定尺寸的方阵写的模板类，并编写了一个矩阵求逆的成员函数。其中矩阵的尺寸我们是通过非类型模板参数指定。

```cpp
template<typename T, std::size_t n>//T为数据类型，n为矩阵大小
class SquareMatrix{
private:
    T data[n * n];
public:
    ……
    void invert();//求逆运算
};
SquareMatrix<double,5> sm1;
sm1.invert(); //调用SquareMatrix<double,5>::invert
SquareMatrix<double,10> sm2;
sm2.invert(); //调用SquareMatrix<double,10>::invert
```

上面会具体化两份invert。这两份函数几乎完全相同（除了一个操作`5*5`矩阵，一个操作`10*10`）。这就是代码膨胀的一个典型例子。

```cpp
template<typename T>
class SquareMatrixBase {
public:
    SquareMatrixBase(std::size_t n, T* pMem): size(n), pData(pMem) {}
    void SetDataPtr(T* ptr) { pData = ptr; }
protected:
    void invert();
private:
    std::size_t size;
    T* pData;
};

template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T>{
private:
    T data[n * n];
public:
    SquareMatrix(): SquareMatrixBase<T>(n, data) { }
    void invert()
    {
        SquareMatrixBase<T>::invsert(n);
    }
};
```

SquareMatrixBase和SquareMatrix不同的是，它只对元素对象的类型进行模板参数化，所以不同尺寸的SquareMatrix会共用同一个SquareMatrixBase。

但上面的实现也有可能会付出一定的代价，因为在SquareMatrixBase中的invert只能在运行时获取尺寸参数size（非编译期常量 ），那么就丧失了生成更佳代码的可能性。

但从另一个角度，避免了代码膨胀，就减小了执行文件的大小，也就因为降低了程序的working set（一组内存页）大小，强化了指令高速缓存内引用集中化（locality of reference）。进而程序会更快。

上面只讨论了非类型模板参数带来的膨胀问题，实际上对于类型参数，比如int和long在很多平台下也会生成完全一样的代码，类似情况，很多平台上对于所有指针类型，底层的实现代码实际也是一致的。比如`list<int*>`、`list<const int*>`、`list<SquareMatrix<long, 3>*>`。