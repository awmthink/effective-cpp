
#include <iostream>
class Widget {
 public:
  Widget() { std::cout << "Widget Ctor" << std::endl; }
  ~Widget() { std::cout << "Widget Dtor" << std::endl; }

 private:
  int value;
};

int main() {
  auto *pw = new Widget[3];
  delete pw;

  auto *pw1 = new Widget;
  delete[] pw;

  return 0;
}
