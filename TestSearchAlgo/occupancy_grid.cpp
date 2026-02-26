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
    // Clear interior first
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            setCell(x, y, FREE);
        }
    }

    // Outer walls
    for (int x = 0; x < width; x++) {
        setCell(x, 0, OBSTACLE);
        setCell(x, height - 1, OBSTACLE);
    }

    for (int y = 0; y < height; y++) {
        setCell(0, y, OBSTACLE);
        setCell(width - 1, y, OBSTACLE);
    }

    // Vertical zig-zag wall
    for (int y = 1; y < 12; y++)
        setCell(3, y, OBSTACLE);

    for (int y = 3; y < 14; y++)
        setCell(6, y, OBSTACLE);

    for (int y = 1; y < 12; y++)
        setCell(9, y, OBSTACLE);

    // Create gaps in walls (so path exists)
    setCell(3, 4, FREE);
    setCell(6, 8, FREE);
    setCell(9, 5, FREE);

    // Narrow corridor block
    for (int x = 10; x < 14; x++)
        setCell(x, 10, OBSTACLE);

    // Dead-end trap
    setCell(11, 6, OBSTACLE);
    setCell(12, 6, OBSTACLE);
    setCell(11, 7, OBSTACLE);
}

void OccupancyGrid::printWithPath(
    const std::vector<std::pair<int,int>>& path) const
{
    std::vector<std::vector<bool>> isPath(height,
        std::vector<bool>(width, false));

    for (auto& p : path)
        isPath[p.second][p.first] = true;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (isPath[y][x])
                std::cout << "* ";
            else if (grid[y][x] == OBSTACLE)
                std::cout << "# ";
            else if (grid[y][x] == FREE)
                std::cout << ". ";
            else
                std::cout << "? ";
        }
        std::cout << "\n";
    }
}
