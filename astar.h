#ifndef ASTAR_H
#define ASTAR_H

#include "occupancy_grid.h"
#include <vector>

struct Node {
    int x, y;
    float g;
    float h;
    float f;
    Node* parent;
};

class AStar {
public:
    AStar(OccupancyGrid& grid);

    bool findPath(int startX, int startY,
                  int goalX, int goalY);

    std::vector<std::pair<int,int>> getPath() const;

private:
    OccupancyGrid& grid;

    float heuristic(int x1, int y1,
                    int x2, int y2) const;

    std::vector<std::pair<int,int>> path;
};

#endif