# Item 02: 尽量以const、enum、inline替换#define

* 对于单纯的常量，最好以const对象或enums替换`#define`
* 对于形式函数的宏（macro），最好以inline函数模板替换`#define`

核心思想就是尽可能的以“编译器替换预处理器”，因为预处理器只是进行匹配与替换，无法在语言语法上进行检查与提示，而编译器是有这个能力的。

对于`# define ASPECT_RATIO 1.653`来说，编译器看不见`ASPECT_RATIO`，它只能看见1.653，`ASPECT_RATIO`不会出现在符号表中，这会对于一些编译错误提示、调试来说都非常不友好。

`const`常量的一个特珠用法是定义在class中：

```cpp
class GamePlayer {
private:
    static const int NumTurns = 5;
    int scores[NumTurns];
};
```

请注意`NumTurns`在类中只是一个声明，而不是定义，但我们确可以直接使用NumTurns的值，因为这属于编译器的优化，但不能取地址，所以不能取NumTurns的指针或把它绑定到一个引用上。如果要定义NumTurns，则需要在一个实现文件中进行定义：

```cpp
const int GamePlayer::NumTurns;
```