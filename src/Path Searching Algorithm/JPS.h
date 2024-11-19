#ifndef JPS_H
#define JPS_H

#include <vector>
#include <utility> // for std::pair

using namespace std;

// === JPS 알고리즘 함수 선언 ===
vector<pair<int, int>> jps(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal);

#endif // JPS_H
