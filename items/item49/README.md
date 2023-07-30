# Item 49: 了解new-handler的行为

* set_new_handler允许客户指定一个函数，在内存分配无法满足时被调用。
* nothrow new是一个颇为局限的工具，因为它只适用于内存分配；后续的构造函数调用还是可能抛出异常。

有些人会吐槽C++没有像Java/.NET那样的垃圾回收能力，但有些人喜欢C++也正是因为C++允许他们手动管理内存，比如像系统程序开发人员，这样的开发人员研究并学习他们的软件使用内存的行为特征，然后修改分配和释放的工作，以追求最佳的效率（包括时间和空间）。

C++对于定制内存申请和释放是通过`operator new`和`operator delete`两个函数完成的，然后还有一个`new-handler`用于给内存不足时的行为提供一定的定制化能力。

由于heap内存是一个全局性的资源，所以多线程环境下的内存管理是一个极大的挑战，这里需求复杂的同步控制。

当operator new抛出异常以反映一个未获满足的内存需求之前，它会先调用一个客户指定的“错误处理函数”，一个所谓的`new-handler`。我们可使用`std`空间下的`set_new_handler`来设计函数对象。

```cpp
typedef void (*new_handler)();
// 设置新的handler，并返回旧的handler
new_handler set_new_handler(new_handler) throw();
```

那么内存不足时，我们设置的`new-handler`到底应该做哪些处理呢？

* 让更多的内存可被使用，一般是需要去释放被管理的，没有用的内存
* 安装另一个new-handler，如果这个handler无法取得更多的内存，它可以安装另外一个new-handler来替换自己。
* 卸载new-handler，也就是把null指针传给set_new_handler。表示现在内存不足已经无能为力了，随后，operator new就会抛出异常。
* 抛出bad_alloc（或派生的bad_alloc）异常。
* 不返回，通过调用abort或exit。

如何为类设置其专属的`new-handler`，C++中没有直接支持。我们可以很容易的支持，只需要在class专属的`operator new`中来设置特定的new handler来替换global handler。

这里我们可以利用RAII的手法以及CRTP来实现一个可以设置new-handler的模板基类。具体可以参考[main.cc](./main.cc)