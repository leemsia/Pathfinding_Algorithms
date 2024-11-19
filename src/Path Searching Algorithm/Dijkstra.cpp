#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

// 사용자 정의 해시 함수 정의
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

// node, weight 설정을 위한 pair 정의
typedef pair<int, int> pii;

// Dijkstra 알고리즘 함수
vector<pair<int, int>> dijkstra(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // 각 노드까지의 최단 거리를 저장하는 2D 벡터 (초기값: 무한대)
    vector<vector<int>> distances(rows, vector<int>(cols, numeric_limits<int>::max()));
    distances[start.first][start.second] = 0;

    // 우선순위 큐 초기화
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({0, start});

    // 이동 가능한 방향
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 경로 추적용 map
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> came_from;

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        auto current = pq.top().second;
        pq.pop();

        if (current == goal) {
            break; // 목표에 도달하면 종료
        }

        // 인접한 노드 탐색
        for (const auto& direction : directions) {
            int new_row = current.first + direction.first;
            int new_col = current.second + direction.second;

            // 맵 경계 및 장애물 체크
            if (new_row < 0 || new_col < 0 || new_row >= rows || new_col >= cols || grid[new_row][new_col] == 1) {
                continue;
            }

            int new_distance = current_distance + 1; // 가중치는 1로 고정

            // 최단 거리 갱신
            if (new_distance < distances[new_row][new_col]) {
                distances[new_row][new_col] = new_distance;
                pq.push({new_distance, {new_row, new_col}});
                came_from[{new_row, new_col}] = current; // 경로 추적
            }
        }
    }

    // 경로 추적
    vector<pair<int, int>> path;
    pair<int, int> current = goal;

    while (came_from.find(current) != came_from.end()) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

/*
int main() {
    // 그래프 정의 (인접 리스트 형태)
    unordered_map<int, vector<pii>> graph;
    graph[1] = {{2, 2}, {3, 4}};
    graph[2] = {{1, 2}, {3, 1}, {4, 7}};
    graph[3] = {{1, 4}, {2, 1}, {4, 3}};
    graph[4] = {{2, 7}, {3, 3}};

    int start_node = 1;
    unordered_map<int, int> distances = dijkstra(graph, start_node);

    cout << "노드 " << start_node << "에서 다른 노드까지의 최단 거리 : \n";
    for (const auto& [node, distance] : distances) {
        cout << "노드 " << start_node << "에서 노드 " << node << "까지의 거리 : ";
        if (distance == numeric_limits<int>::max()) {
            cout << "도달 불가\n";
        } else {
            cout << distance << "\n";
        }
    }

    return 0;
}
*/