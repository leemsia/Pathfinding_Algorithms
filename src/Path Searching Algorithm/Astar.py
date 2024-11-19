import heapq
import math

# 휴리스틱 함수 : 유클리드 거리 계산 (노드 간의 직선 거리)
def heuristic(node1, node2):
    x1, y1 = node1
    x2, y2 = node2
    return math.sqrt((x1 - x2) **2 + (y1 - y2) **2)

def a_star(graph, start, goal):
    # 각 노드까지의 실제 거리 저장할 딕셔너리 (초기값 : 무한대)
    g_costs = {node: float('inf') for node in graph}
    g_costs[start] = 0

    # 우선순위 큐 초기화
    priority_queue = [(0, start)] # (f(n), node)
    came_from = {} # 경로 추적을 위한 딕셔너리

    while priority_queue:
        # 현재 노드를 큐에서 꺼냄
        current_f_cost, current_node = heapq.heappop(priority_queue)

        # 목표 노드에 도달한 경우 경로를 반환
        if current_node == goal:
            path = []
            total_cost = g_costs[goal]
            while current_node in came_from:
                path.append(current_node)
                current_node = came_from[current_node]
            path.append(start)
            return path[::-1], total_cost # 경로를 시작부터 끝까지로 반환
        
        # 인접 노드를 탐색
        for neighbor, cost in graph[current_node]:
            tentative_g_cost = g_costs[current_node] + cost
            if tentative_g_cost < g_costs[neighbor]:
                # 새로운 최단 거리 발견
                g_costs[neighbor] = tentative_g_cost
                f_cost = tentative_g_cost + heuristic(neighbor, goal)
                heapq.heappush(priority_queue, (f_cost, neighbor))
                came_from[neighbor] = current_node

    return None, None # 경로가 없는 경우

# 그래프 정의 (인접 리스트)
# 노드 위치가 좌표 (x, y)로 정의됨
graph = {
    (0, 0): [((2, 0), 3), ((0, 2), 2)],
    (2, 0): [((0, 0), 3), ((2, 2), 5), ((4, 0), 2)],
    (0, 2): [((0, 0), 2), ((2, 2), 4)],
    (2, 2): [((2, 0), 5), ((0, 2), 4), ((4, 2), 3)],
    (4, 0): [((2, 0), 2), ((4, 2), 1)],
    (4, 2): [((2, 2), 3), ((4, 0), 1), ((4, 4), 2)],
    (4, 4): [((4, 2), 2)]
}

start = (0, 0)
goal = (4, 4)
path, total_cost = a_star(graph, start, goal)

print("최단 경로 : ", path)
print("가중치 합 : ", total_cost)