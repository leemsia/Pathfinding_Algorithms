#include <iostream>
#include <memory>

using namespace std;

class class_object {
public:
  class_object() {
    cout << "�޸𸮰� �Ҵ� �Ǿ����ϴ�." << endl;
  };
  ~class_object() {
    cout << "�޸𸮰� ���� �Ǿ����ϴ�." << endl;
  };
  void print_out() {
    cout << "��ü�� �Լ��� ȣ���մϴ�." << endl;
  };
};

int main() {
  // ����Ʈ �����ͷ� �޸� ���� ����
  unique_ptr<class_object> unique_pointer(new class_object());
  unique_pointer->print_out();
  return 0;
}