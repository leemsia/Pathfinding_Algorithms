// heuristic.h
#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <cmath>
#include <utility>

inline double heuristic(std::pair<int, int> node1, std::pair<int, int> node2) {
    int x1 = node1.first, y1 = node1.second;
    int x2 = node2.first, y2 = node2.second;
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

#endif // HEURISTIC_H
