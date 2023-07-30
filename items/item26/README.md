# Item 26: 尽可能延后变量定义的出现时间

* 尽可能延后变量定义式的出现。这样做可增加程序的清晰度并改善程序效率。

```cpp
std::string encryptPassword(const std::string& password) {
  using namespace std;
  string encrypted;
  if (password.length() < MinimumPasswordLength) {
    throw logic_error("Password is too short");
  }
  // 将一个加密后的密码放到encrypted中
  return encrypted
}
```

在上面加密的代码中，当传入的代码较短时，会触发异常，这时候，对于encrypted变量的定义就变得没有意义，白花掉了构造与析构的开销。

```cpp
std::string encryptPassword(const std::string& password) {
  using namespace std;
  if (password.length() < MinimumPasswordLength) {
    throw logic_error("Password is too short");
  }
  string encrypted;
  // 将一个加密后的密码放到encrypted中
  return encrypted
}
```