#include <iostream>

using namespace std;

struct bomb {
  void operator()() {
    cout << "��!" << endl;
  }

  void operator()(int range) {
    cout << "�ݰ� " << range << "m�� �÷��̾� ����!" << endl;
  }
};

int main() {
  bomb mine;

  mine();
  mine(30);

  return 0;
}