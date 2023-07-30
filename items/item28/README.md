# Item 28: 避免返回handles指向对象内部成分

* 避免返回handles（包括reference、指针、迭代器）指向对象内部。遵守这个条款可以增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码牌”的可能性降至最低。

下面的代吗中Point是表示坐标系中点的类，RectData表示一个矩形的左上角与右下角点的点坐标。Rectangle是一个矩形的类，包含了一个指向RectData的指针。

```cpp
class Point {
public:
    Point(int x, int y);
    void SetX(int newVal);
    void SetY(int newVal);
private:
    int x_cor;
    int y_cor;
};

struct RectData {
    Point ulhc;    // 矩形左上角的点
    Point lrhc;    // 矩形右上角的点
};

class Rectangle {
private:
    shared_ptr<RectData> pData;
public:
    Point& upperLeft( const{ return pData->lrhc; }
    Point& lowerRight() const{ return pData->ulhc; }
};
```

我们可以看到了uppLeft和lowerRight是两个const成员函数，它们的功能只是想向客户提供两个Rectangle相关的坐标点，而不是让客户修改Rectangle。但是两个函数却都返回了references指向了private内部数据，调用者于是可以通过references更改内部数据。

这给了我们一些警示：成员变量的封装性只等于“返回其reference”的函数的访问级别；如果const成员函数传出一个reference，后者所指数据与对象自身有关联，而它又被存储于对象之外，那么这个函数的调用者可以修改那笔数据。

handles(号码牌，用于取得某个对象)指reference、指针和迭代器，它们返回一个“代表对象内部数据”的handle。

我们可以对上面的成员函数返回类型上加上const来解决问题：

```cpp
public:
    const Point& upperLeft()const{ return pData->lrhc; }
    const Point& lowerRight()const{ return pData->ulhc; }
```

但是函数返回一个handle代表对象内部成分还总是危险的，因为可能会造成dangling handles(空悬的号牌)。比如某个函数返回GUI对象的外框（bounding box）。

```cpp
class GUIObject{
    //..
};
const Rectangle boundingBox(const GUIObject&obj);        
GUIObject* pgo;
const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
```

对boundingBox的调用返回的是一个临时对象，这个对象没有名称，随后我们调用了这个对象的upperLeft，返回了一个指向临时对象内部数据的reference。但是在语句结束后，这个临时对象会被销毁，pUpperLeft会变成空悬的、虚吊的(dangling)！

有一个handle被传出来去，一旦如此你就是暴露在“handle比其所指对象更长寿“的风险下。

这并不意味你绝对不可以让成员函数返回 handle。有时候你必须那么做。例如operator[]就允许你“摘采”strings 和 vectors 的个别元素，而这些 operator[]s就是返回 references 指向“容器内的数据”，那些数据会随着容器被销毁而销毁。尽管如此，这样的函数毕竟是例外，不是常态。