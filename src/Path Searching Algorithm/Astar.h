#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> astar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal);

#endif