#include "JPS.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>


using namespace std;

const int CELL_SIZE = 50;
const int GRID_ROWS = 5;
const int GRID_COLS = 5;

// 맵 데이터
vector<vector<int>> grid = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

pair<int, int> start = {0, 0};
pair<int, int> goal = {4, 4};

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