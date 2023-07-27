#include <stdexcept>
#include <vector>

class Widget {
 public:
  Widget(int value) : i(value) {}
  ~Widget() {
    if (i == 42) {
      throw std::runtime_error("42");
    }
  }

 private:
  int i;
};

class DBConnection {
 public:
  void close();
};

class DBConn {
 public:
  void close() {
    db.close();
    closed = true;
  }
  ~DBConn() {
    if (!closed) {
      try {
        db.close();
      } catch (...) {
        // 制作运转记录，记下对close的调用失败
      }
    }
  }

 private:
  bool closed;
  DBConnection db;
};

int main() {
  std::vector<Widget> ws;
  ws.emplace_back(42);
  ws.emplace_back(1);
  ws.emplace_back(42);

  return 0;
}