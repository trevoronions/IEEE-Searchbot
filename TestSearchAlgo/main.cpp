#include "occupancy_grid.cpp"
#include "astar.cpp"
#include <iostream>

int main() {

    OccupancyGrid grid(15, 15);
    grid.loadTestMap();   

    AStar planner(grid);

    if (planner.findPath(1, 1, 13, 13)) {

        auto path = planner.getPath();

        for (auto& p : path) {
            grid.setCell(p.first, p.second, FREE);
        }

        std::cout << "Path found!\n";
    } else {
        std::cout << "No path found.\n";
    }

    grid.printWithPath(planner.getPath());

    return 0;
}