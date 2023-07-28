# Item 22: 将成员变量声明为private


将成员设置为private，对于它们的访问都是通过成员函数，带来的好处：

首先是代码的一致性，调用public成员时不用考虑是成员还是函数，其次封装性，都写成函数进行访问可以提供以后修改访问方法的可能性，而不影响使用方法。封装保证了用户不能随意读写对象内的数组，使得对象永远处于一个正常的状态，保持成员的约束条件成立。另外，public影响的是所有使用者，而protected影响的是所有继承者，都影响巨大。

```cpp
class SpeedDataCollection {
private:
  int avgSpeed;
public:
  void addValue(int speed); // 添加一笔新数据
  double averageSoFar() const; // 返回平均速度
};
```

对于`averageSoFar`我们可以选择2种计算方式：1）惰性求值，把每一笔speed都缓存住，只有在调用了averageSoFar时才真正计算；2）在addValue时就更新平均速度，而averageSoFar的调用只是简单把内部的avgSpeed返回回去。

选择哪一种实现方式可能要根据具体的运行环境等多个条件来综合考虑，但使用函数来返回avgSpeed就为随时修改实现提供了一种灵活性。


* 切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺条件获得保证，并提供class作者以充分的实现弹性。
* protected并不比public更具封装性。