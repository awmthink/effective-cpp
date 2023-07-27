
class Uncopyable {
 protected:
  Uncopyable() = default;
  ~Uncopyable() = default;

 private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

// 由于Widget内的base class不可copy构造和copy assignment
// 所以编译将Widget的copy构造和copy assignment标记为delete
class Widget : private Uncopyable {};

int main() {
  Widget w1;
  Widget w2 = w1;
}