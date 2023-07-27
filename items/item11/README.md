# Item 11: 在`operator=`中处理自我赋值

* 确保当对象自我赋值时`operator=`有良好的行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy-and-swap。
* 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

对象的自我赋值听起来很傻，但有时代码里可能会出现一些潜在的自我赋值：

```cpp
a[i] = a[j];
*px = *py;
```

不正确的版本：

```cpp
class Bitmap {};
class Widget {
  Widget& operator=(const Widget& rhs) {
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
  }

 private:
  Bitmap* pb;
};
```

看似没问题，实际有异常安全的问题：


```cpp
class Bitmap {};
class Widget {
  Widget& operator=(const Widget& rhs) {
    if (this == &rhs) return;
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
  }

 private:
  Bitmap* pb;
};
```

如果在new过程中抛出了异常（Bitmap构造函数抛出异常或内存不足），则当前对象变成一个不完整的对象。

交换一下delete和new语句的顺序：


```cpp
Widget& operator=(const Widget& rhs) {
  Bitmap* new_pb = new Bitmap(*rhs.pb);
  delete pb;
  pb = new_pb;
  return *this;
}
```
这个版本是异常安全的，而且把自我赋值的判断去掉了，因为`opeator=`具备“异常安全性”时，往往自动获得“自我赋值安全”的回报。这时，如果自我赋值，则相当于把pb新拷贝构造了一份。

要不要保留这个证同（`if (this == &rhs) return;`）的测试的呢？答案是否，因为自我赋值发生的概率很低，但拷贝赋值函数被调用的机会就很大了，每次都多做一次证同测试，会大大降低执行速度。因为分支语句十分影响：Prefetching、caching和Pipelining等指令的效率。

swap版本：

```cpp
class Widget {
  Widget& operator=(const Widget& rhs) {
    Widget temp(rhs); // 这里发生异常的话，也没有任何影响
    Swap(temp);
    return *this;
  }

  void Swap(Widget &rhs) noexcept {
    std::swap(pb, rhs.pb);
  }

 private:
  Bitmap* pb;
};
```

pass-by-value的方式：

```cpp
Widget& operator=(Widget rhs) {
    Swap(temp);
    return *this;
  }
```

在C++11中，它同时也是移动赋值运算符。