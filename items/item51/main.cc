#include <cstdlib>
#include <new>

class Base {
 public:
  static void *operator new(std::size_t size) {
    if (size != sizeof(Base)) {
      return ::operator new(size);
    }
    while (true) {
      void *p = std::malloc(size);
      if (p) {
        return p;
      }
      std::new_handler global_handler = std::get_new_handler();
      std::set_new_handler(global_handler);
      if (global_handler) {
        (*global_handler)();
      } else {
        throw std::bad_alloc();
      }
    }
  }
};

int main() { return 0; }
