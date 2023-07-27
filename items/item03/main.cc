#include <cstdint>
#include <cstring>

class TextBook {
 public:
  const char &operator[](std::size_t pos) const {
    // bounds checking
    // log acess data
    // verify data integrity
    return pText[pos];
  }

  char &operator[](std::size_t pos) {
    return const_cast<char &>(static_cast<const TextBook &>(*this)[pos]);
  }

  std::size_t length() const {
    if (!lengthIsValid) {
      textLength = std::strlen(pText);
      lengthIsValid = true;
    }
    return textLength;
  }

 private:
  char *pText;
  mutable std::size_t textLength;
  mutable bool lengthIsValid;
};

int main() {}