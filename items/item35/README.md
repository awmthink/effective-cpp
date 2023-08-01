# 考虑virtual函数以外的其他选择

* virtual 函数的替代方案包括NVI手法及Strategy设计模式的多种形式。NVI手法自身是一个特珠形式的Template Method模式
* 将功能从成员函数移动到class外部函数，带来的一个缺点是非成员函数无法访问class的non-public成员。
* tr1::function对象的行为就是一般函数指针，这样的对象可以接纳“与给定之目标签名式兼容”的所有可调用物。

`GameCharacter`是一个表现游戏中人物的类，它可能是一个继承体系下的基类，因为游戏中有同类型的人物。`healthValue()`用于返回人物的健身指数，在游戏中不同的人物在被伤害后，健康状态的下降计算方式不同。

```cpp
class GameCharacter {
public:
    // 返回人物的健康指数，Derived classeds可重新定义它。
    virtual int healthValue() const;
};
```

## 手法一：以Non-Virtual Interface（NVI）实现Template Method模式

这个流派主张virtual函数应该几乎总是private。

```cpp
class GameCharacter {
public:
    // 返回人物的健康指数，Derived classeds可重新定义它。
    int healthValue() const {
        ... // 做一些事前工作
        int retValue = doHealthValue();
        ... // 做一些事后工作
        return retValue;
    }
private:
    virtual int doHealthValue() const {
        // 缺省的实现，计算健康指数。
    }
};
```

NVI 手法的一个优点隐身在上述代码注释“做一些事前工作”和“做一些事后工作” 之中。那些注释用来告诉你当时的代码保证在“virtual 函数进行真正工作之前和之后”被调用。这意味外覆器（wrapper）确保得以在一个virtual 函数被调用之前设定好适当场景，并在调用结束之后清理场景。“事前工作”可以包括锁定互斥器 （locking a mutex）、制造运转日志记录项 （log entry）、验证class 约束条件、验证函数先决条件等等。“事后工作”可以包括互斥器解除锁定(unlocking a mutex)、验证函数的事后条件、再次验证class 约束条件等等。如果你让客户直接调用 virtual函数，就没有任何好办法可以做这些事。


## 手法二：由函数指针实现Strategy模式

```cpp
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
 public:
  using HealthCalcFunc = int (*)(const GameCharacter&);

  explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
      : healthFunc{hcf} {}
  // 返回人物的健康指数，Derived classeds可重新定义它。
  int healthValue() const { return healthFunc(*this); }

 private:
  HealthCalcFunc healthFunc;
};
```

这个做法是常见的Strategy设计模式的简单应用。如果我们把它和上面虚函数的实现比较的话，它的灵活性，在于同一个人物类型的不同对象可以有不同的健康计算函数。以及人物的健康计算函数可以在运行时进行变更。但它也有一定的缺点，由于真正的健康指数计算的函数是外部提供的，所以函数无法访问到GameCharacter的私有成员。

我们可以把上面`HealthCalcFunc`定义为一个更通用的函数对象，也就是用`std::function`来表示，这样，我们就可以传入函数对象，函数指针，lambda表达式了，更加灵活。

## 手法三：更加古典的Strategy模式

把HealthClacFunc做成一个继承体系：

```cpp
class GameCharacter;
class HealthCalcFunc() {
public:
    virtual int calc(const GameCharacter& gc) const {}
};

HealthCalcFunc defaultHealthCalc;

class GameCharacter {
 public:
  explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc)
      : pHealthFunc{phcf} {}
  int healthValue() const { return pHealthFunc->calc(*this); }

 private:
  HealthCalcFunc pHealthFunc;
};
```



