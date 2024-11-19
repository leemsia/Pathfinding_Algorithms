#include <iostream>

using namespace std;

template <typename T = int>   // �⺻ ���� ����
class data_package {
public:
  data_package(T first) : first(first) {}
  void print_out_element() {
    cout << "Ŭ���� ���ø� ���� �Ű� ���� �� : " << first << endl;
  }
private:
  T first;
};

int main() {
  data_package<> template_inst1(5);   // �⺻ ����(���⼭�� int)���� ����
  data_package<string> template_inst2("Ŭ���� ���ø� �⺻��");

  template_inst1.print_out_element();
  template_inst2.print_out_element();
}
