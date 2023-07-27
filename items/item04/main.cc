class Widget {
 public:
  Widget() {}
  Widget(int sz) : size(sz), pArray(new int[size]) {}

 private:
  int *pArray;
  int size;
};

Widget &GetWidget() {
  static Widget w;
  return w;
}

int main() {}