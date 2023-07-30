#include <iostream>

class Base {
 protected:
  int b;

 public:
  virtual void SetValue(int v) { b = v; }
  virtual ~Base() = default;
};

class Derived : Base {
 private:
  int d;

 public:
  virtual void SetValue(int v) {
    // static_cast<Base>(*this).SetValue(v);
    Base::SetValue(v);
    d = 2 * v;
  }
  void PrintValue() { std::cout << "b: " << b << ", d: " << d << std::endl; }
};

int main() {
  Derived d;
  d.SetValue(1);
  d.PrintValue();
  return 0;
}