#include "Dijkstra.h"
#include "Astar.h"
#include "JPS.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/resource.h>

using namespace std;

const int CELL_SIZE = 20;
const int GRID_ROWS = 30;
const int GRID_COLS = 30;
const int OBSTACLE_COUNT = 100;

vector<vector<int>> grid;
pair<int, int> start = {0, 0};
pair<int, int> goal = {29, 29};

void printMemoryUsage(const std::string& algorithmName) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    std::cout << algorithmName << " Memory usage: " << usage.ru_maxrss / 1024.0 << " MB" << std::endl;
}

// 랜덤 맵 생성 함수
vector<vector<int>> generateRandomMap(int rows, int cols, int obstacleCount) {
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    srand(time(0));

    while (obstacleCount > 0) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (grid[r][c] == 0) {
            grid[r][c] = 1;
            --obstacleCount;
        }
    }

    grid[start.first][start.second] = 0;
    grid[goal.first][goal.second] = 0;

    return grid;
}

void drawGrid(sf::RenderWindow& window) {
    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);

            if (grid[row][col] == 1) {
                cell.setFillColor(sf::Color::Black);
            } else {
                cell.setFillColor(sf::Color::White);
            }

            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(200, 200, 200));
            window.draw(cell);
        }
    }
}

void displayAlgorithmName(sf::RenderWindow& window, const string& algorithmName) {
    sf::Font font;
    if (!font.loadFromFile("Arial Unicode.ttf")) {
        cout << "Failed to load font!" << endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Algorithm: " + algorithmName);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, GRID_ROWS * CELL_SIZE + 10);

    window.clear(sf::Color::White);
    drawGrid(window);
    window.draw(text);
    window.display();

    this_thread::sleep_for(chrono::seconds(1));
}

void animatePath(sf::RenderWindow& window, const vector<pair<int, int>>& path, const sf::Color& color) {
    for (auto pos : path) {
        int row = pos.first;
        int col = pos.second;

        window.clear(sf::Color::White);
        drawGrid(window);

        sf::RectangleShape startCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        startCell.setPosition(start.second * CELL_SIZE, start.first * CELL_SIZE);
        startCell.setFillColor(sf::Color::Blue);
        window.draw(startCell);

        sf::RectangleShape goalCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        goalCell.setPosition(goal.second * CELL_SIZE, goal.first * CELL_SIZE);
        goalCell.setFillColor(sf::Color::Red);
        window.draw(goalCell);

        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);
        cell.setFillColor(color);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color(200, 200, 200));
        window.draw(cell);

        window.display();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
// === 알고리즘 실행 및 결과 출력 함수 ===
vector<pair<int, int>> executeAlgorithm(
    const string& algorithmName,
    vector<pair<int, int>> (*algorithm)(const vector<vector<int>>&, pair<int, int>, pair<int, int>),
    sf::Color pathColor,
    sf::RenderWindow& window
) {
    // 알고리즘 실행
    auto startTime = chrono::high_resolution_clock::now();
    vector<pair<int, int>> path = algorithm(grid, start, goal);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

    // 결과 출력
    cout << algorithmName << " 경로 길이: " << path.size()
         << ", 실행 시간: " << duration / 1000.0 << " ms" << endl;

    printMemoryUsage(algorithmName);

    // 애니메이션 실행
    displayAlgorithmName(window, algorithmName);
    animatePath(window, path, pathColor);

    return path;
}

// === 메인 함수 ===
int main() {
    // 랜덤 맵 생성
    grid = generateRandomMap(GRID_ROWS, GRID_COLS, OBSTACLE_COUNT);

    // 시작점과 목표점 유효성 검사
    if (grid[start.first][start.second] == 1 || grid[goal.first][goal.second] == 1) {
        cout << "Error: Start or Goal position is blocked!" << endl;
        return 1;
    }

    // 디버깅용: 맵 출력
    cout << "Generated Map:" << endl;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell == 1 ? '#' : '.') << " ";
        }
        cout << endl;
    }
    cout << endl;

    // SFML 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE + 50), "Pathfinding Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 알고리즘 실행 및 시각화
        executeAlgorithm("Dijkstra", dijkstra, sf::Color::Yellow, window);
        executeAlgorithm("A*", astar, sf::Color::Cyan, window);
        executeAlgorithm("JPS", jps, sf::Color::Green, window);

        break; // 애니메이션 실행 후 종료
    }

    return 0;
}