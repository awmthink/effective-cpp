#include <iostream>

class Widget {
 public:
  void swap(Widget &rhs) noexcept { std::swap(p, rhs.p); }

 private:
  int *p = nullptr;
};

// 优先级最高被查找
void swap(Widget &lhs, Widget &rhs) noexcept {
  std::cout << "global swap()" << std::endl;
  lhs.swap(rhs);
}

namespace std {
// 第2优先级被查找
template <>
void swap<Widget>(Widget &lhs, Widget &rhs) {
  std::cout << "std::swap()" << std::endl;
  lhs.swap(rhs);
}

}  // namespace std

int main() {
  using std::swap;
  Widget w1, w2;
  std::swap(w1, w2);

  return 0;
}