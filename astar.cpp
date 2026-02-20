#include "astar.h"
#include <queue>
#include <cmath>
#include <unordered_set>
#include <algorithm>

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f; // min heap
    }
};

AStar::AStar(OccupancyGrid& g) : grid(g) {}

float AStar::heuristic(int x1, int y1,
                       int x2, int y2) const {
    // Manhattan distance
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool AStar::findPath(int startX, int startY,
                     int goalX, int goalY)
{
    std::priority_queue<Node*, std::vector<Node*>, Compare> open;

    std::vector<std::vector<bool>> closed(
        grid.getHeight(),
        std::vector<bool>(grid.getWidth(), false)
    );

    Node* start = new Node{
        startX, startY,
        0,
        heuristic(startX,startY,goalX,goalY),
        0,
        nullptr
    };
    start->f = start->g + start->h;

    open.push(start);

    while (!open.empty()) {

        Node* current = open.top();
        open.pop();

        if (current->x == goalX &&
            current->y == goalY)
        {
            // reconstruct path
            path.clear();
            while (current != nullptr) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        closed[current->y][current->x] = true;

        // 4-directional movement
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!grid.inBounds(nx, ny)) continue;
            if (grid.getCell(nx, ny) == OBSTACLE) continue;
            if (closed[ny][nx]) continue;

            float newG = current->g + 1;

            Node* neighbor = new Node{
                nx, ny,
                newG,
                heuristic(nx,ny,goalX,goalY),
                0,
                current
            };

            neighbor->f = neighbor->g + neighbor->h;
            open.push(neighbor);
        }
    }

    return false;
}

std::vector<std::pair<int,int>> AStar::getPath() const {
    return path;
}