# Item 11 优先考虑使用deleted函数而非使用未定义的私有声明

- ⽐起声明函数为 private 但不定义，使⽤deleted函数更好
- 任何函数都能被删除（be deleted），包括⾮成员函数和模板实例（译注：实例化的函数）
