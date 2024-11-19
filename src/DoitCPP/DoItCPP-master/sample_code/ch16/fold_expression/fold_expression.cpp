#include <iostream>

using namespace std;

template<typename doll>
doll show_doll(doll doll_name) {
  return "'" + doll_name + "' ���ʿ� ";
}

template<typename... dolls>
string find_doll(dolls... doll_list) {
  // ���� ǥ���� ���
 return (show_doll(doll_list) + ...);
}

int main() {
  cout << "ù��° ��Ʈ���ī ";
  cout << find_doll(string("����"), string("����"), string("����"));
  cout << "�ֽ��ϴ�." << endl << endl;

  cout << "�ι�° ��Ʈ���ī ";
  cout << find_doll(string("Ư����"), string("����"), string("����"), string("����"), string("�ؼ���"));
  cout << "�ֽ��ϴ�." << endl;

  return 0;
}