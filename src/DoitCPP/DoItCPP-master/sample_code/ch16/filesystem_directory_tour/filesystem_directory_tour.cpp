#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main() {

  fs::current_path("..");
  fs::path path_obj(fs::current_path());
  
  cout << fs::canonical(path_obj) << " - ���� ���丮 �� ����" << endl;
  for (auto const & dir : fs::directory_iterator(path_obj)) {
    cout << dir.path().relative_path() << endl;
  }

  cout << endl << fs::canonical(path_obj) << " - ���� ���丮 ��ȸ" << endl;
  for (auto const& dir : fs::recursive_directory_iterator(path_obj)) {
    cout << dir.path().relative_path() << endl;
  }

  fs::space_info disk_info = fs::space(path_obj);
  cout << endl << "��ũ �뷮:" << disk_info.capacity << endl
    << "��ũ ���뷮:" << disk_info.available << endl;

  return 0;
}