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

// ���� ��ü�� ���޹޾� Ư���� Ʃ�÷� ��ȯ
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
  // �� Ʃ�� ����
  return make_tuple(monster_type, monster_name, hp, power);
}

// Ʃ���� ���� ���
void print_out_tuple(tuple<int, string, int, int> monster_status) {
  cout << get<1>(monster_status) << "(" 
      << get<0>(monster_status) << ") : hp(" 
      << get<2>(monster_status) << "), power(" 
      << get<3>(monster_status) << ")" << endl;
}

// tuple size ��� ���� ����ϴ� �ҽ� �ڵ� cppreference.com ����
// https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat
template<class tuple_obj, std::size_t N>
struct print_out_tuple_second {
  static void show(const tuple_obj& t)
  {
    print_out_tuple_second<tuple_obj, N - 1>::show(t);
    std::cout << ", " << std::get<N - 1>(t);
  }
};

template<class tuple_obj>
struct print_out_tuple_second<tuple_obj, 1> {
  static void show(const tuple_obj& t)
  {
    std::cout << std::get<0>(t);
  }
};

int main() {

  monster_a monster_a_inst;
  monster_b monster_b_inst;

  // make_tuple�� ������ Ʃ���� ��ȯ �޾� Ʃ�� ��ü�� ����
  tuple<int, string, int, int> monster_a_status = get_monster_status(monster_a_inst);
  // �� ���� �����ڷ� Ʃ�� ����
  tuple<int, string, int, int> monster_a_status_copy(monster_a_status);
  // �� ������ �ʱ�ȭ�� Ʃ�� ����
  tuple<int, string, int, int> monster_b_status_temp{monster_b_type, "B ���� �ӽ�", 100, 100};
  // �� auto ���
  auto monster_b_status = get_monster_status(monster_b_inst);

  print_out_tuple(monster_a_status);
  print_out_tuple(monster_a_status_copy);
  print_out_tuple(monster_b_status_temp);

  // �� Ʃ���� ���ڰ� ��ȯ
  swap(monster_b_status, monster_b_status_temp);
  cout << "Ʃ�� ���� ��ȯ ��" << endl;
  print_out_tuple(monster_b_status_temp);

  // �� Ʃ�� ��ġ��
  auto monster_status_all = tuple_cat(monster_a_status, monster_b_status);
  cout << "tuple_cat ȣ�� ���� : { ";
  print_out_tuple_second<decltype(monster_status_all), tuple_size<decltype(monster_status_all)>::value>::show(monster_status_all);
  cout << "}" << endl;
  return 0;
}