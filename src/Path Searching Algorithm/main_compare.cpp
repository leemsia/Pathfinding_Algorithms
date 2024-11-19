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

using namespace std;

const int CELL_SIZE = 20;
const int GRID_ROWS = 30;
const int GRID_COLS = 30;
const int OBSTACLE_COUNT = 100;

vector<vector<int>> grid;
pair<int, int> start = {0, 0};
pair<int, int> goal = {29, 29};

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

int main() {
    grid = generateRandomMap(GRID_ROWS, GRID_COLS, OBSTACLE_COUNT);

    if (grid[start.first][start.second] == 1 || grid[goal.first][goal.second] == 1) {
        cout << "Error: Start or Goal position is blocked!" << endl;
        return 1;
    }

    cout << "Generated Map:" << endl;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell == 1 ? '#' : '.') << " ";
        }
        cout << endl;
    }
    cout << endl;

    sf::RenderWindow window(sf::VideoMode(GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE + 50), "Pathfinding Visualization");

    auto startTime = chrono::high_resolution_clock::now();
    vector<pair<int, int>> jpsPath = jps(grid, start, goal);
    auto endTime = chrono::high_resolution_clock::now();
    auto jpsDuration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "JPS 경로 길이: " << jpsPath.size() << ", 실행 시간: " << jpsDuration / 1000.0 << " ms" << endl;

    startTime = chrono::high_resolution_clock::now();
    vector<pair<int, int>> dijkstraPath = dijkstra(grid, start, goal);
    endTime = chrono::high_resolution_clock::now();
    auto dijkstraDuration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Dijkstra 경로 길이: " << dijkstraPath.size() << ", 실행 시간: " << dijkstraDuration / 1000.0 << " ms" << endl;

    startTime = chrono::high_resolution_clock::now();
    vector<pair<int, int>> aStarPath = astar(grid, start, goal);
    endTime = chrono::high_resolution_clock::now();
    auto aStarDuration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "A* 경로 길이: " << aStarPath.size() << ", 실행 시간: " << aStarDuration / 1000.0 << " ms" << endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        displayAlgorithmName(window, "Dijkstra");
        animatePath(window, dijkstraPath, sf::Color::Yellow);

        displayAlgorithmName(window, "A*");
        animatePath(window, aStarPath, sf::Color::Cyan);

        displayAlgorithmName(window, "JPS");
        animatePath(window, jpsPath, sf::Color::Green);

        break; // 애니메이션 실행 후 종료
    }

    return 0;
}
