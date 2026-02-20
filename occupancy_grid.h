#ifndef OCCUPANCY_GRID_H
#define OCCUPANCY_GRID_H

#include <vector>
#include <iostream>

enum CellState {
    UNKNOWN = -1,
    FREE = 0,
    OBSTACLE = 100
};

class OccupancyGrid {
private:
    int width;
    int height;
    float resolution;  // meters per cell (ex: 0.1m)

    std::vector<std::vector<int>> grid;

public:
    OccupancyGrid(int w, int h, float res = 0.1f);

    int getWidth() const;
    int getHeight() const;

    bool inBounds(int x, int y) const;

    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);

    void print() const;

    void loadTestMap();  // temporary for simulation
};

#endif
