// 示例了如何利用std::shared_ptr的自定义删除器功能来自动释放资源

#include <memory>
#include <mutex>

int main() {
  std::mutex mut;
  mut.lock();
  std::shared_ptr<int>(nullptr, [&mut](int *) { mut.unlock(); });
  return 0;
}