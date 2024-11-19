import matplotlib.pyplot as plt
import numpy as np

# 데이터 정의
algorithms = ['Dijkstra', 'A*', 'JPS']
execution_time = [1.321, 0.624, 0.273]  # 실행 시간 (ms)
memory_usage = [23532, 29888, 30456]    # 메모리 사용량 (MB)
path_length = [59, 31, 26]              # 경로 길이

# 1. 실행 시간 비교 그래프
plt.figure(figsize=(8, 5))
plt.bar(algorithms, execution_time, color='skyblue', label='Execution Time (ms)')
plt.title('Execution Time Comparison')
plt.ylabel('Time (ms)')
plt.xlabel('Algorithm')
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()

# 2. 메모리 사용량 비교 그래프
plt.figure(figsize=(8, 5))
plt.bar(algorithms, memory_usage, color='lightcoral', label='Memory Usage (MB)')
plt.title('Memory Usage Comparison')
plt.ylabel('Memory Usage (MB)')
plt.xlabel('Algorithm')
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()

# 3. 경로 길이 비교 그래프
plt.figure(figsize=(8, 5))
plt.plot(algorithms, path_length, marker='o', color='limegreen', label='Path Length')
plt.title('Path Length Comparison')
plt.ylabel('Path Length')
plt.xlabel('Algorithm')
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()
