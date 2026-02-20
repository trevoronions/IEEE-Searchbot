#include "occupancy_grid.h"

int main() {
    OccupancyGrid grid(15, 15);

    grid.loadTestMap();
    grid.print();

    return 0;
}