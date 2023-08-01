# 确定你的public继承建模出is-a关系

* “public继承“意味着is-a。适用于base classes身上的每一件事情一定也适用于derived class身上，因为每一个derived class对象也都是一个base classes对象。

class D（"Derived"）以public形式继承 class B（"base"），意味着每一个类型为D的对象同时也是一个类型为B的对象，反之不成立。B比D表现出更一般化的概念，而D比B表现出更特殊的概念。B对象可以派上用场的任何地方，D对象一样可以派上用场，因为每一个D对象都是一种B对象，反之如果你需要一个D对象，B对象则无法效劳。

```cpp
class Person {};
class Student: public Person {};
```

根据生活经验，每个学生都是人，而并非每个人都是学生。我们预期对人可以成立的每一件事，对学生也成立。

```cpp
void eat(const Person &p);
void study(const Student& s);

Person p;
Student s;

eat(p);     // OK
eat(s);     // OK
study(p);   // OK
study(s);   // 错误
```

public继承和is-a之间的等价关系听起来颇为简单，但有很多直觉上的概念可能会误导我们，比如：企鹅是种鸟，这是事实，鸟可以飞，这也是事实，但企鹅并不会飞。如果我们对企鹅和鸟用public继承来建模，就会遇到这个问题。

另外一个例子是：正方形可以pulbic继承自长方形吗？但如果考虑下面的函数：

```cpp
void makeBigger(Rectangle& r) {
    int oldHeight = r.height();
    r.setWidth(r.width() + 10);
    assert(r.height() == oldHeight);
}
```

如果我们把一个Square传入`makeBigger`接口，那么我们的Square对象就被破坏了，因为它只改变了宽度。显然这里违反了一个事实：“长方形可以独立的修改高度或宽度，但正方形不行”。从这个角度来看，我们使用public继承来建模就是不合适的。