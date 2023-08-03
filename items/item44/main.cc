#include <cstdint>

template <typename T>
class SquareMatrixBase {
 protected:
  // 把SquareMatrix的模板参数n，作为了invert的参数
  void invert(std::size_t matrixSize);
};

template <typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
 private:
  using SquareMatrixBase<T>::invert;  // 编码遮掩base中的invert
 public:
  void invert() { this->invsert(n); }
};