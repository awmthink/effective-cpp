#include <iostream>
#include <new>

template <typename T>
class NewHandlerSupport {
 public:
  static std::new_handler set_new_handler(std::new_handler p) noexcept;
  static void* operator new(std::size_t size);

 private:
  static std::new_handler currentHandler;
};

// new_handler的资源管理类，析构时自动还原全局的new_handler
class NewHandlerHolder {
 public:
  explicit NewHandlerHolder(std::new_handler nh) : handler(nh) {}
  ~NewHandlerHolder() { std::set_new_handler(handler); }

 private:
  std::new_handler handler;
};

template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(
    std::new_handler p) noexcept {
  std::new_handler oldHandler = currentHandler;
  currentHandler = p;
  return oldHandler;
}

template <typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) noexcept {
  NewHandlerHold h(std::set_new_handler(currentHandler));
  return ::operator new(size);
}

// CRTP
class Widget : public NewHandlerSupport<Widget> {};

int main() {}