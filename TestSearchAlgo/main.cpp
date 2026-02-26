#include "occupancy_grid.cpp"

int main() {
    OccupancyGrid grid(15, 15);

    grid.loadTestMap();
    grid.print();

    return 0;
}