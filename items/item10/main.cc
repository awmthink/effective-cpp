#include <iostream>
#include <stdexcept>
#include <vector>

class Widget {
 public:
  Widget(int v) : value(v) {}
  Widget& operator=(const Widget& w) { return *this; }
  int Value() const { return value; }

 private:
  int value;
};

int main() {
  Widget w1{1};
  Widget w2{2};
  // w2 = w1 返回的是绑定到w2的引用
  std::cout << (w2 = w1).Value() << std::endl;  // Print 2

  return 0;
}