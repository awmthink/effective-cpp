#include <cstring>
#include <memory>
#include <string>

class BorrowableItem {
 public:
  void checkOut(int) {}
};

class ElectronicGadget {
 public:
  bool checkOut() const {}
};

class MP3Player : public BorrowableItem, public ElectronicGadget {};

class IPerson {
 public:
  virtual ~IPerson() = default;
  virtual std::string name() const = 0;
  virtual std::string birthDate() const = 0;

  static std::shared_ptr<IPerson> makePerson(int personIdentifier) {}
};

class PersonInfo {
 public:
  explicit PersonInfo(int id);
  virtual ~PersonInfo();
  virtual const char* theName() const {}
  virtual const char* theBirthDate() const {}

 private:
  virtual const char* valueDelimOpen() const { return "["; }
  virtual const char* valueDelimClose() const { return "]"; }
};

class CPerson : public IPerson, private PersonInfo {  // 多重继承
 public:
  explicit CPerson(int db_id) : PersonInfo(db_id) {}
  virtual std::string name() const {
    return PersonInfo::theName();  // 借由PersonInfo实现
  }
  virtual std::string birthDate() const {
    return PersonInfo::theBirthDate();  // 借由PersonInfo实现
  }

 private:
  // 重新定义继承而来的界限函数
  virtual const char* valueDelimOpen() const { return ""; }
  virtual const char* valueDelimClose() const { return ""; }
};

int main() {
  MP3Player mp;
  mp.BorrowableItem::checkOut(32);
}