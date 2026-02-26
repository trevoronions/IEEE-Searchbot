#include "occupancy_grid.h"

OccupancyGrid::OccupancyGrid(int w, int h, float res)
    : width(w), height(h), resolution(res)
{
    grid.resize(height, std::vector<int>(width, UNKNOWN));
}

int OccupancyGrid::getWidth() const {
    return width;
}

int OccupancyGrid::getHeight() const {
    return height;
}

bool OccupancyGrid::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

int OccupancyGrid::getCell(int x, int y) const {
    if (!inBounds(x, y)) return OBSTACLE; // treat out of bounds as wall
    return grid[y][x];
}

void OccupancyGrid::setCell(int x, int y, int value) {
    if (inBounds(x, y)) {
        grid[y][x] = value;
    }
}

void OccupancyGrid::print() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == UNKNOWN) std::cout << "? ";
            else if (grid[y][x] == FREE) std::cout << ". ";
            else if (grid[y][x] == OBSTACLE) std::cout << "# ";
        }
        std::cout << "\n";
    }
}

void OccupancyGrid::loadTestMap() {
    // Simple box with obstacle inside
    for (int x = 0; x < width; x++) {
        setCell(x, 0, OBSTACLE);
        setCell(x, height - 1, OBSTACLE);
    }

    for (int y = 0; y < height; y++) {
        setCell(0, y, OBSTACLE);
        setCell(width - 1, y, OBSTACLE);
    }

    setCell(5, 5, OBSTACLE);
    setCell(6, 5, OBSTACLE);
    setCell(7, 5, OBSTACLE);

    // Make interior free
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (getCell(x, y) != OBSTACLE)
                setCell(x, y, FREE);
        }
    }
}
