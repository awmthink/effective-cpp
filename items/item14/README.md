# Item 14: 在资源管理类中小心coping行为

* 复制RAII对象必须一并复制它所管理的资源，所以资源的coping行为决定RAII对象的coping行为
* 普遍而常见的RAII class copying行为是：抑制copying、使用引用计数法。

如果我们要使用的资源不是内存，就不能使用智能指针了，这时候，我们要学会创建自己的资源管理类。

```cpp
class File {
  File(int file_handle):fd(file_handle) {}
  ~File() { close(fd); }
private:
  int fd;
}
```

对于上面文件句柄的管理类`File`来说，它在析构时，会调用close函数来关闭文件。假如我们对File对象进行拷贝的话，就会出问题：

```cpp
File f1(file_handle);
File f2(f1);
```

f1和f1在释放时，都会调用close()来关闭内部的描述符，但它们实际上指向的同一个打开的文件。那么如何处理这种资源管理类的coping行为呢：

* 禁止复制。许多时候对RAII对象进行复制是一个不合理的行为。
* 对底层资源使用“引用计数器”，我们可以使用shared_ptr，然后自定义删除器。
* 复制底部的资源，也就是深度拷贝。
* 转换底部资源的拥有权。C++98中的auto_ptr的拷贝行为就是这样。

因为coping函数，如果我们没定义，有可能被编译器合成出来，而合成出来的coping函数，对于资源管理类来说，一般都是不合适的，所以我们需要记得编写它们。