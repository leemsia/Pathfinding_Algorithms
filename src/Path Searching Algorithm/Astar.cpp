#include "Astar.h"
#include "heuristic.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

// 사용자 정의 해시 함수
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

/*
// 두 좌표 사이의 유클리드 거리 (휴리스틱)
double heuristic(pair<int, int> node1, pair<int, int> node2) {
    int x1 = node1.first, y1 = node1.second;
    int x2 = node2.first, y2 = node2.second;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
*/

// A* 알고리즘 (그리드 기반)
vector<pair<int, int>> astar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // 각 노드의 g-cost 저장
    unordered_map<pair<int, int>, double, pair_hash> g_costs;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> came_from;

    // 초기화
    g_costs[start] = 0;

    // 우선순위 큐
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<>> pq;
    pq.push({heuristic(start, goal), start});

    // 이동 가능한 방향
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // 상하좌우
        {-1, -1}, {1, 1}, {1, -1}, {-1, 1} // 대각선
    };

    while (!pq.empty()) {
        auto [current_f_cost, current_node] = pq.top();
        pq.pop();

        if (current_node == goal) {
            // 목표 도달 시 경로 추적
            vector<pair<int, int>> path;
            while (came_from.find(current_node) != came_from.end()) {
                path.push_back(current_node);
                current_node = came_from[current_node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& direction : directions) {
        int new_row = current_node.first + direction.first;
        int new_col = current_node.second + direction.second;

        // 맵 경계 및 장애물 체크
        if (new_row < 0 || new_col < 0 || new_row >= rows || new_col >= cols || grid[new_row][new_col] == 1) {
            continue;
        }

        // === 대각선 이동 시 중간 장애물 체크 ===
        if (abs(direction.first) == 1 && abs(direction.second) == 1) { // 대각선 방향
            int intermediate_row = current_node.first + direction.first; // 세로 이동
            int intermediate_col = current_node.second;                 // 가로 이동
            int intermediate_col_alt = current_node.second + direction.second; // 대각선 이동의 두 경로

            if (grid[intermediate_row][current_node.second] == 1 && grid[current_node.first][intermediate_col_alt] == 1) {
                continue; // 중간 장애물이 있으면 대각선 이동 차단
            }
        }

        // g-cost 계산
        double new_g_cost = g_costs[current_node] + (abs(direction.first) + abs(direction.second) == 2 ? sqrt(2) : 1);

        if (g_costs.find({new_row, new_col}) == g_costs.end() || new_g_cost < g_costs[{new_row, new_col}]) {
            g_costs[{new_row, new_col}] = new_g_cost;
            double f_cost = new_g_cost + heuristic({new_row, new_col}, goal);
            pq.push({f_cost, {new_row, new_col}});
            came_from[{new_row, new_col}] = current_node;
        }
    }

    }

    return {}; // 경로가 없는 경우
}

/*
int main() {
    // 그래프 정의
    unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>, hash_pair> graph;
    graph[{0, 0}] = {{{2, 0}, 3}, {{0, 2}, 2}};
    graph[{2, 0}] = {{{0, 0}, 3}, {{2, 2}, 5}, {{4, 0}, 2}};
    graph[{0, 2}] = {{{0, 0}, 2}, {{2, 2}, 4}};
    graph[{2, 2}] = {{{2, 0}, 5}, {{0, 2}, 4}, {{4, 2}, 3}};
    graph[{4, 0}] = {{{2, 0}, 2}, {{4, 2}, 1}};
    graph[{4, 2}] = {{{2, 2}, 3}, {{4, 0}, 1}, {{4, 4}, 2}};
    graph[{4, 4}] = {{{4, 2}, 2}};

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};
    auto [path, total_cost] = a_star(graph, start, goal);

    cout << "최단 경로 : \n";
    for (const auto& node : path) {
        cout << "(" << node.first << "," << node.second << ") ";
    }
    cout << "\n총 가중치 합 : " << total_cost << endl;

    return 0;
}
*/