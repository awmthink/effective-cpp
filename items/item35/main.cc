

class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
 public:
  using HealthCalcFunc = int (*)(const GameCharacter&);

  explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
      : healthFunc{hcf} {}
  // 返回人物的健康指数，Derived classeds可重新定义它。
  int healthValue() const { return healthFunc(*this); }

 private:
  HealthCalcFunc healthFunc;
};

int main() {}