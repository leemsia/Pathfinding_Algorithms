#include <iostream>

using namespace std;

class monster {
public:
  void create_monster() = delete;
  //void create_monster_() {}; // delete Ű���带 ������� �ʰ� ����
};

int main() {
  monster monster_sample;

  // �Ʒ� �� ���� ������ �߻��մϴ�.
  monster_sample.create_monster();
  monster_sample.create_monster_();
  return 0;
}