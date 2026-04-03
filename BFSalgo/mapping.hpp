#pragma once
#include "grid.hpp"

struct Point2D{
    float x, y;
};

Point2D polarToCartesian(float r, float degrees);

int worldToGrid(float worldVal, float scale);

void drawLine(Grid2D& grid, int x0, int y0, int x1, int y1);
