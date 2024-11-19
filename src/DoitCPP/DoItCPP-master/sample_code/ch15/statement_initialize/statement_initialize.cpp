#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

constexpr int even = 0;
constexpr int odd = 1;

int main() {
  array<int, 5> data_array{47, 23, 58, 10, 36};

  // if ���� �ʱ�ȭ ���� ���
  if (auto element = data_array[3]; element > 20 ) {
    cout << "�� ��° ��Ұ��� 20���� Ů�ϴ�." << endl;
  }
  else {
    cout << "�� ��° ��Ұ��� 20���� �۰ų� �����ϴ�." << endl;
  }

  // switch ���� �ʱ�ȭ ���� ���
  switch (auto element = data_array[4] % 2 ; element) {
  case odd:
    cout << "�ټ� ��° ��Ұ��� Ȧ�� �Դϴ�." << endl;
    break;
  case even:
    cout << "�ټ� ��° ��Ұ��� ¦�� �Դϴ�." << endl;
    break;
  }

  // ���� ��� for ���� �ʱ�ȭ ���� ���
  for (sort(data_array.begin(), data_array.end()); auto&& element : data_array) {
    cout << element << ", ";
  }
  cout << endl;

  return 0;
}