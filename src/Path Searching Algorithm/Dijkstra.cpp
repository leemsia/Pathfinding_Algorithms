#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

// node, weight 설정을 위한 pair 정의
typedef pair<int, int> pii;

// Dijkstra 알고리즘 함수
unordered_map<int, int> dijkstra(const unordered_map<int, vector<pii>>& graph, int start) {
    // 각 노드까지의 최단 거리를 저장하는 unordered_map (초기값 : 무한대)
    unordered_map<int, int> distances;
    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;

    // 우선순위 큐 초기화 (first : 거리, second : node 인 pair)
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        // 이미 처리된 노드라면 건너뛴다
        if (current_distance > distances[current_node]) {
            continue;
        }

        // 인접한 노드와 가중치 확인
        for (const auto& neighbor : graph.at(current_node)) {
            int adjacent = neighbor.first;
            int weight = neighbor.second;
            int distance = current_distance + weight;

            // 최단 거리를 갱신할 수 없는 경우
            if (distance < distances[adjacent]) {
                distances[adjacent] = distance;
                pq.push({distance, adjacent});
            }
        }
    }

    return distances;
}

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