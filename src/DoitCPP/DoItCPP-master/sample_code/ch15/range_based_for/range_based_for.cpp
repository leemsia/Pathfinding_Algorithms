#include <iostream>
#include <array>

using namespace std;

int main(void) {
  array<int, 10> numbers { 7, 8, 2, 5, 3, 9, 0, 4, 1, 6 };

  // for ���� Ȱ�� �迭 ���
  for (int i = 0; i < 10; ++i) {
    cout << numbers[i] << " , ";
  }
  cout << endl;

  void* test = nullptr;

  // ���� ��� for ���� Ȱ�� �迭 ���
  for ( auto &value : numbers) {
    cout << value << " , ";
  }
  cout << endl;

  return 0;
}