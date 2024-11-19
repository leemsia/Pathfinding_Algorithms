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

int GRID_ROWS; // 사용자 입력으로 설정
int GRID_COLS; // 사용자 입력으로 설정
int OBSTACLE_COUNT; // 사용자 입력으로 설정

vector<vector<int>> grid;
pair<int, int> start;
pair<int, int> goal;

// 랜덤 맵 생성 함수
vector<vector<int>> generateRandomMap(int rows, int cols, int obstacleCount) {
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    srand(time(0)); // 랜덤 시드 설정

    while (obstacleCount > 0) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (grid[r][c] == 0) { // 이미 장애물이 없는 곳만 선택
            grid[r][c] = 1; // 장애물 배치
            --obstacleCount;
        }
    }
    return grid;
}

// 맵 출력 함수
void printMap(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell == 1 ? '#' : '.') << " ";
        }
        cout << endl;
    }
    cout << endl;
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

void animatePath(sf::RenderWindow& window, const vector<pair<int, int>>& path) {
    for (auto pos : path) {
        int row = pos.first;
        int col = pos.second;

        // 화면 초기화 및 맵 재그리기
        window.clear(sf::Color::White); // 화면 초기화
        drawGrid(window);              // 맵 다시 그리기

        // 시작점과 목표점 다시 그리기
        sf::RectangleShape startCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        startCell.setPosition(start.second * CELL_SIZE, start.first * CELL_SIZE);
        startCell.setFillColor(sf::Color::Blue);
        window.draw(startCell);

        sf::RectangleShape goalCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        goalCell.setPosition(goal.second * CELL_SIZE, goal.first * CELL_SIZE);
        goalCell.setFillColor(sf::Color::Red);
        window.draw(goalCell);

        // NPC 경로 표시
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);
        cell.setFillColor(sf::Color::Green);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color(200, 200, 200));
        window.draw(cell);

        // 화면 업데이트
        window.display();

        // 이동 속도 조절
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}


int main() {
    // 사용자 입력 받기
    cout << "Enter grid size (rows cols): ";
    cin >> GRID_ROWS >> GRID_COLS;

    cout << "Enter number of obstacles: ";
    cin >> OBSTACLE_COUNT;

    cout << "Enter start position (row col): ";
    cin >> start.first >> start.second;

    cout << "Enter goal position (row col): ";
    cin >> goal.first >> goal.second;

    // 랜덤 맵 생성
    grid = generateRandomMap(GRID_ROWS, GRID_COLS, OBSTACLE_COUNT);

    // 시작점과 목표점 유효성 검사
    if (grid[start.first][start.second] == 1 || grid[goal.first][goal.second] == 1) {
        cout << "Error: Start or Goal position is blocked!" << endl;
        return 1;
    }

    // 디버깅용: 맵 출력
    cout << "Generated Map:" << endl;
    printMap(grid);

    // SFML 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE), "JPS Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 맵 그리기
        window.clear(sf::Color::White);
        drawGrid(window);

        // 시작점과 목표점 표시
        sf::RectangleShape startCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        startCell.setPosition(start.second * CELL_SIZE, start.first * CELL_SIZE);
        startCell.setFillColor(sf::Color::Blue);
        window.draw(startCell);

        sf::RectangleShape goalCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        goalCell.setPosition(goal.second * CELL_SIZE, goal.first * CELL_SIZE);
        goalCell.setFillColor(sf::Color::Red);
        window.draw(goalCell);

        // JPS 알고리즘 실행 및 경로 시각화
        vector<pair<int, int>> path = jps(grid, start, goal);
        animatePath(window, path);

        window.display();
        break; // 애니메이션 후 종료
    }

    return 0;
}