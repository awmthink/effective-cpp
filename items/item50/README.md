# Item 50: 了解new和delete的合理替换时机

* 有许多理由需要写个自定义的new和delete，包括改善性能、对heap运用错误进行调试、收集heap使用信息。

什么时候需要替换编译器提供的operator new/delete呢？

* 用于检测运用上的错误；比如通过记录申请和释放的次数与大小来统计是否有内存泄漏；或者可以分配额外的空间放置特定的byte pattern，然后程序结束时检查有没有发生overrun或underrun。
* 为了强化效率。编译器带的Operator new/delete主要是通用，它必须处理一系列需求，包括大块的内存，小块的内存，大小混合型内存；它们必须接纳各种分配形态，范围从程序存活期间的少量区域动态分配，到大量短命对象的持续分配和归还。它们还必须考虑碎片问题。如果你对你的程序的动态内存运用型态有深刻的了解，通常可以发现，定制版性能可以胜过缺省版本。
* 为了收集使用上的统计数据。在一头栽进定制new/delete里之前，我们应该先收集我们的软件如何使用动态内存、分配区域大小分布如何？寿命分布如何？它们是倾向以FIFO次序还是FIFO次序或随机次序来分配与归还。在程序执行不的阶段是否会改变这些特性与分布。
* 为了降低缺省内存管理器带来的空间额外开销。
* 为了弥补缺省分配器中非最佳对齐。

即使考虑到上面这么多，很多时候也是非必要的，某些编译器已经在它们的内存管理管理中支持切换至调试状态和日志版本。同时也有一些商业产品和开源的内存管理器，或者能够更好的满足我们的需求。

许多 C++ 书籍，包括本书早期版本，都曾展示高效率的小型对象分配器源码，但它们往往漏掉可移植性和齐位考虑、线程安全性······等等令人生厌的麻烦细节。真正称得上程序库者，必然稳健强固。

观念上，写一个定制的operator new十分简单，下面是一个快速实现的用于检测overruns（在分配的区域尾端写入）或underruns（在分配区域的起点前写入）的版本。

```cpp
static const int signature = 0xDEADBEEF;
using Byte = unsigned char;

void* operator new(std::size_t size) {
  std::size_t realSize = size + 2 * sizeof(int);

  void* pMem = malloc(realSize);
  if (!pMem) throw std::bad_alloc();

  *(static_cast<int*>(pMem)) = signature;
  *(reinterpret_cast<int*>(static_cast<Byte*>(pMem) + realSize - sizeof(int))) =
      signature;
  return static_cast<Byte*>(pMem) + sizeof(int);
}
```

上面的这个版本有很多细节都没有考虑，比如没有包括处理new-handler的循环，没有考虑引入`signature`后而导致的内存对齐问题。