#include <iostream>

using namespace std;

class character {
public:
  character() : hp(100), power(100) {};

protected:
  int hp;
  int power;
};

//character Ŭ������ ��� ���� player Ŭ����
class player : public character {
public:
  player() {};
};

//�⺻ Monster Ŭ����
class monster {
public:
  monster() {};

protected:
  void get_damage(int _damage) {};
  void attack(player target_player) {};
  void attack_special(player target_player);
};

void monster::attack_special(player target_player) {
  cout << "�⺻ ���� : ������ - 10 hp" << endl;
}

//���� A�� �⺻ Monster Ŭ�����κ��� ���
class monster_a : public monster, character {
public:
  using monster::get_damage;
private:
  //��ӹ��� �Լ� �������̵� 
  void attack_special(player target_player);
};

void monster_a::attack_special(player target_player) {
  cout << "���ޱ� ���� : ������ - 15 hp" << endl;
}

//���� A�� �⺻ Monster Ŭ�����κ��� ���
class monster_b : public monster, character {
private:
  //��ӹ��� �Լ� �������̵� 
  void attack_special(player target_player);
};

void monster_b::attack_special(player target_player) {
  cout << "���� ���� : ������ - 0 hp" << endl;
}

int main() {
  monster_a mon_1;
  monster_b mon_2;

  mon_1.get_damage(100);
  // �Ʒ� �ڵ�� ������ �߻��մϴ�.
  mon_2.get_damage(100);

  return 0;
}