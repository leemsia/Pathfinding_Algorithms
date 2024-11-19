#include <iostream>
#include <tuple>

using namespace std;

const int monster_a_type = 0;
const int monster_b_type = 1;
const int monster_c_type = 2;

class monster {
public:
  int get_monster_type() { return monster_type; };

protected:
  int monster_type;

private:
  int location_x;
  int location_y;
};

//���� A�� �߻� Ŭ���� Monster Ŭ�����κ��� ���
class monster_a : public monster {
public:
  monster_a() {
    monster_type = monster_a_type;
  };
};


//���� B�� �߻� Ŭ���� Monster Ŭ�����κ��� ���
class monster_b : public monster {
public:
  monster_b() {
    monster_type = monster_b_type;
  };
};


//���� C�� �߻� Ŭ���� Monster Ŭ�����κ��� ���
class monster_c : public monster {
public:
  monster_c() {
    monster_type = monster_c_type;
  };
};

tuple<int, string, int, int> get_monster_status(monster& monster_inst) {

  int monster_type = monster_inst.get_monster_type();
  string monster_name;
  int hp(100), power(100);

  switch (monster_type) {
  case monster_a_type:
    monster_name = "A ����";
    hp += 10;
    break;
  case monster_b_type:
    monster_name = "B ����";
    power += 20;
    break;
  case monster_c_type:
    monster_name = "C ����";
    hp -= 10;
    power += 100;
    break;
  }

  return make_tuple(monster_type, monster_name, hp, power);
}

void print_out_tuple(tuple<int, string, int, int> monster_status) {
  cout << get<1>(monster_status) << "(" << get<0>(monster_status)
    << ") : hp(" << get<2>(monster_status) << "), power(" << get<3>(monster_status)
    << ")" << endl;
}

int main() {
  monster_a monster_a_inst;

  tuple<int, string, int, int> monster_a_status = get_monster_status(monster_a_inst);
  auto[monster_type, monster_name, hp, power] = get_monster_status(monster_a_inst);

  print_out_tuple(monster_a_status);
  cout << "������ ���ε����� ���ҵ� Ʃ��" << endl << monster_name << "(" << monster_type << ") : hp(" << hp << "), power(" << power << ")" << endl;

  return 0;
}