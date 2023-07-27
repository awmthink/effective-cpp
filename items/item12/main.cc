
#include <string>

class Data {};

class Customer {
 public:
  Customer() = default;
  Customer(const Customer &rhs) { *this = rhs; }
  Customer &operator=(const Customer &rhs) { new (this) Customer(rhs); }

 private:
  std::string name;
  Data lastTransaction;
};

class PriorityCustomer : public Customer {
  PriorityCustomer(const PriorityCustomer &rhs)
      : Customer(rhs), priority(rhs.priority) {}

  PriorityCustomer &operator=(const PriorityCustomer &rhs) {
    Customer::operator=(rhs);
    priority = rhs.priority;
    return *this;
  }

 private:
  int priority;
};

int main() {
  Customer c1;
  Customer c2(c1);

  return 0;
}