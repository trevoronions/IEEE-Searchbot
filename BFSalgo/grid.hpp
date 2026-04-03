#pragma once
#include <vector>
#include <iostream>

enum class Cell : int{ 
    UNKNOWN = 0, 
    FREE = 1,
    OBSTRUCTED = 2
};

struct Grid2D {
    int width, height;
    std::vector<std::vector<Cell>> cells;

    Grid2D(int w, int h, Cell defaultCell = Cell::UNKNOWN); // declaration only

    void set(int x, int y, Cell value);   // declaration only
    Cell get(int x, int y) const;         // declaration only
    bool inBounds(int x, int y) const;    // declaration only
    void display() const;                 // declaration only
};