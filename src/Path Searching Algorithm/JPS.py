import math
import heapq

# 휴리스틱 함수 (유클리드 거리)
def heuristic(node1, node2):
    x1, y1 = node1
    x2, y2 = node2
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

# 점프 함수
def jump(grid, current, direction, goal):
    x, y = current
    dx, dy = direction

    while True:
        x += dx
        y += dy

        # 디버깅: 현재 위치와 방향
        print(f"Jumping to ({x}, {y}) in direction ({dx}, {dy})")

        # 맵 경계 체크
        if x < 0 or y < 0 or x >= len(grid) or y >= len(grid[0]) or grid[x][y] == 1:
            print(f"Out of bounds or hit obstacle at ({x}, {y})")
            return None

        # 목표에 도달
        if (x, y) == goal:
            print(f"Reached goal at ({x}, {y})")
            return (x, y)

        # 강제 점프 포인트 체크
        if dx != 0 and dy != 0:  # 대각선 이동
            if (grid[x - dx][y] == 1 and grid[x][y - dy] == 0) or (grid[x][y - dy] == 1 and grid[x - dx][y] == 0):
                print(f"Found forced jump point at ({x}, {y}) (diagonal)")
                return (x, y)
        elif dx != 0:  # 수평 이동
            if (y > 0 and grid[x][y - 1] == 1) or (y < len(grid[0]) - 1 and grid[x][y + 1] == 1):
                print(f"Found forced jump point at ({x}, {y}) (horizontal)")
                return (x, y)
        elif dy != 0:  # 수직 이동
            if (x > 0 and grid[x - 1][y] == 1) or (x < len(grid) - 1 and grid[x + 1][y] == 1):
                print(f"Found forced jump point at ({x}, {y}) (vertical)")
                return (x, y)

        # 대각선 이동 중 추가 점프
        if dx != 0 and dy != 0:
            next_jump_x = jump(grid, (x, y), (dx, 0), goal)
            next_jump_y = jump(grid, (x, y), (0, dy), goal)
            if next_jump_x or next_jump_y:
                print(f"Found diagonal jump point at ({x}, {y})")
                return (x, y)

# JPS 탐색 함수
def jps(grid, start, goal):
    open_set = []
    heapq.heappush(open_set, (0 + heuristic(start, goal), 0, start))  # (f, g, node)
    came_from = {}
    g_costs = {start: 0}

    # 가능한 이동 방향
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (1, 1), (1, -1), (-1, 1)]

    while open_set:
        _, g, current = heapq.heappop(open_set)

        # 디버깅: 현재 처리 중인 노드
        print(f"Processing node: {current}, g = {g}")

        # 목표 지점 도달
        if current == goal:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            print("Found path:", path[::-1])
            return path[::-1]  # 경로 반환

        # 모든 방향 탐색
        for direction in directions:
            jump_point = jump(grid, current, direction, goal)
            if jump_point:
                tentative_g = g + heuristic(current, jump_point)

                # 디버깅: 점프 포인트와 비용
                print(f"Jump point: {jump_point}, tentative_g = {tentative_g}")

                if jump_point not in g_costs or tentative_g < g_costs[jump_point]:
                    g_costs[jump_point] = tentative_g
                    f = tentative_g + heuristic(jump_point, goal)
                    heapq.heappush(open_set, (f, tentative_g, jump_point))
                    came_from[jump_point] = current
                    print(f"Added to open set: {jump_point} with f = {f}")

    print("경로를 찾을 수 없습니다_jps.")
    return None  # 경로를 찾을 수 없는 경우

# 테스트 맵 정의
grid = [
    [0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0],
    [0, 0, 0, 1, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0]
]

start = (0, 0)
goal = (4, 4)

path = jps(grid, start, goal)
if path:
    print("최단 경로:", path)
else:
    print("경로를 찾을 수 없습니다.")
