#include <iostream>
#include <stdexcept>
#include <vector>

// 所有交易的base class
class Transaction {
 public:
  Transaction() {
    // 永远只会调用base class的LogTransactions
    LogTransaction();
  }
  // 做出一份因类型不同而不同的日志记录
  virtual void LogTransaction() const = 0;
};

class BuyTransaction : public Transaction {
 public:
  virtual void LogTransaction() const {}
};

class SellTransaction : public Transaction {
 public:
  virtual void LogTransaction() const {}
};

class Base {
 public:
  Base() {
    std::cout << "Base::Ctor()" << std::endl;
    std::cout << typeid(*this).name() << std::endl;
  }
};

class Derived : public Base {
 public:
  Derived() {
    std::cout << "Derived::Ctor()" << std::endl;
    std::cout << typeid(*this).name() << std::endl;
  }
};

int main() {
  Derived d;
  // Output:
  // Base::Ctor()
  // 4Base
  // Derived::Ctor()
  // 7Derived

  return 0;
}