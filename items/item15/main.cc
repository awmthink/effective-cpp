

// FontHandle是C中代表字体资源的抽象
typedef struct _FontHandle {
}* FontHandle;

// 字体相关的一些C API
FontHandle getFont();
void releaseFont(FontHandle fh);
void changFontSize(FontHandle, int font_size);

// FontHandle的资源管理内
class Font {
 public:
  explicit Font(FontHandle fh) : f(fh) {}

  ~Font() { releaseFont(f); }

  FontHandle get() const { return f; }

  operator FontHandle() const { return f; }

 private:
  FontHandle f;
};

int main() {
  Font f(getFont());
  int newFontSize = 14;
  // 显式的获取原始资源
  changFontSize(f.get(), newFontSize);
  // 这里通过隐式的自动类型转换，把Font转换为了FontHandle
  changFontSize(f, newFontSize);

  // 隐式转换的风险：
  FontHandle f2 = f;  // 问题语句，并不是执行的Font对象拷贝构造
}
