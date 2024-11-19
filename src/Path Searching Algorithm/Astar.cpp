#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <utility>
#include <limits>

using namespace std;

// 해시 함수 정의
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

// 두 좌표 사이의 유클리드 거리 (휴리스틱)
double heuristic(pair<int, int> node1, pair<int, int> node2) {
    int x1 = node1.first, y1 = node1.second;
    int x2 = node2.first, y2 = node2.second;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 -  y2));
}

// A* 알고리즘
pair<vector<pair<int, int>>, double> a_star(
    const unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>, hash_pair>& graph,
    pair<int, int> start, pair<int, int> goal) {
        unordered_map<pair<int, int>, double, hash_pair> g_costs;
        unordered_map<pair<int, int>, pair<int, int>, hash_pair> came_from;

        for (const auto& node : graph) {
            g_costs[node.first] = numeric_limits<double>::infinity();
        }
        g_costs[start] = 0;

    // 우선순위 큐 선언
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_f_cost, current_node] = pq.top();
        pq.pop();

        if (current_node == goal) {
            vector<pair<int, int>> path;
            double total_cost = g_costs[goal]; // 최단 경로의 총 가중치
            while (came_from.find(current_node) != came_from.end()) {
                path.push_back(current_node);
                current_node = came_from[current_node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return {path, total_cost};
        }

        for (const auto& [neighbor, cost] : graph.at(current_node)) {
            double tentative_g_cost = g_costs[current_node] + cost;
            if (tentative_g_cost < g_costs[neighbor]) {
                g_costs[neighbor] = tentative_g_cost;
                double f_cost = tentative_g_cost + heuristic(neighbor, goal);
                pq.push({f_cost, neighbor});
                came_from[neighbor] = current_node;
            }
        }
    }
    return {{}, numeric_limits<double>::infinity()}; // 경로가 없는 경우
}

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