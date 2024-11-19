#include "JPS.h"
#include "heuristic.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

// === 사용자 정의 해시 함수 및 동등 비교 함수 ===
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // XOR 연산으로 해시 값 결합
    }
};

/*
// === 휴리스틱 함수 ===
double heuristic(pair<int, int> node1, pair<int, int> node2) {
    int x1 = node1.first, y1 = node1.second;
    int x2 = node2.first, y2 = node2.second;
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
*/

// === 점프 함수 ===
pair<int, int> jump(const vector<vector<int>>& grid, pair<int, int> current, pair<int, int> direction, pair<int, int> goal) {
    int x = current.first, y = current.second;
    int dx = direction.first, dy = direction.second;

    while (true) {
        x += dx;
        y += dy;

        // === 맵 경계 및 장애물 체크 ===
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] == 1) {
            return {-1, -1}; // 장애물 또는 맵 경계
        }

        // === 목표 지점 도달 ===
        if (make_pair(x, y) == goal) {
            return {x, y}; // 목표에 도달
        }

        // === 강제 점프 포인트 탐지 ===
        if (dx != 0 && dy != 0) { // 대각선 이동
            if ((grid[x - dx][y] == 1 && grid[x][y - dy] == 0) || (grid[x][y - dy] == 1 && grid[x - dx][y] == 0)) {
                return {x, y};
            }
        } else if (dx != 0) { // 수평 이동
            if ((y > 0 && grid[x][y - 1] == 1) || (y < grid[0].size() - 1 && grid[x][y + 1] == 1)) {
                return {x, y};
            }
        } else if (dy != 0) { // 수직 이동
            if ((x > 0 && grid[x - 1][y] == 1) || (x < grid.size() - 1 && grid[x + 1][y] == 1)) {
                return {x, y};
            }
        }

        // === 대각선 이동 중 추가 점프 ===
        if (dx != 0 && dy != 0) {
            // 수평 및 수직 경로가 모두 유효한지 검사
            if (grid[x - dx][y] == 1 && grid[x][y - dy] == 1) {
                return {-1, -1}; // 대각선 이동 불가
            }

            // 수평 또는 수직 방향의 점프 포인트 확인
            auto next_jump_x = jump(grid, {x, y}, {dx, 0}, goal);
            auto next_jump_y = jump(grid, {x, y}, {0, dy}, goal);

            if (next_jump_x.first != -1 || next_jump_y.first != -1) {
                return {x, y};
            }
        }
    }
}

// === JPS 탐색 함수 ===
vector<pair<int, int>> jps(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    // 우선순위 큐 정의
    priority_queue<tuple<double, double, pair<int, int>>, vector<tuple<double, double, pair<int, int>>>, greater<>> open_set;

    // 경로 추적용 딕셔너리
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> came_from;

    // g(n) 비용 저장용 딕셔너리
    unordered_map<pair<int, int>, double, pair_hash> g_costs;

    // 탐색 방향 정의
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0},  // 위, 아래
        {0, -1}, {0, 1},  // 왼쪽, 오른쪽
        {-1, -1}, {1, 1}, // 왼쪽 위, 오른쪽 아래
        {-1, 1}, {1, -1}  // 오른쪽 위, 왼쪽 아래
    };

    // 시작 지점 초기화
    open_set.push({0 + heuristic(start, goal), 0, start});
    g_costs[start] = 0;

    while (!open_set.empty()) {
        auto [_, g, current] = open_set.top();
        open_set.pop();

        // === 목표 지점 도달 시 경로 반환 ===
        if (current == goal) {
            vector<pair<int, int>> path;
            while (came_from.find(current) != came_from.end()) {
                path.push_back(current);
                current = came_from[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        // === 모든 방향 탐색 ===
        for (const auto& direction : directions) {
            auto jump_point = jump(grid, current, direction, goal);
            if (jump_point.first != -1) {
                double tentative_g = g + heuristic(current, jump_point);

                if (g_costs.find(jump_point) == g_costs.end() || tentative_g < g_costs[jump_point]) {
                    g_costs[jump_point] = tentative_g;
                    double f = tentative_g + heuristic(jump_point, goal);
                    open_set.push({f, tentative_g, jump_point});
                    came_from[jump_point] = current;
                }
            }
        }
    }

    return {}; // 경로를 찾을 수 없는 경우
}
/*
// === 메인 함수 ===
int main() {
    // 맵 정의 (0 : 이동 가능, 1 : 장애물)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    auto path = jps(grid, start, goal);

    if (!path.empty()) {
        cout << "최단 경로 : ";
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "경로를 찾을 수 없습니다." << endl;
    }

    return 0;
}
*/