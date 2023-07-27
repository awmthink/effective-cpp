class Widget {
 public:
  Widget(int v) : a(v) {}

 private:
  const int a;
};

int main() {
  Widget w(1);
  Widget w2(2);
  // cannot be assigned because its copy assignment operator is implicitly
  // deleted 
  w2 = w;
}