#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> dijkstra(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal);

#endif