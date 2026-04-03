#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "mapping.hpp"

Point2D polarToCartesian(float r, float degrees) {
    float radians = degrees * (M_PI / 180.0f);
    return {
        r * cosf(radians), r * sinf(radians)};
}

int worldToGrid(float worldVal, float scale) {
    return static_cast<int>(std::round(worldVal / scale));
}

static void drawLineHorizontal(Grid2D& grid, int x0, int y0, int x1, int y1) {
    std::cout << "Horizontal" << std::endl;
    bool c = 0;

    if (x0 > x1) {  // If starting point is higher than end flip values
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::cout << "Swapped xy initial with xy final" << std::endl; // Testing
        c = 1;
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    int dir; //determining direction of slope
    if (dy < 0){
        dir = -1;
    }
    else{
        dir = 1;
    }
    dy *= dir;

    if (dx != 0){
        int y = y0;
        int p = 2*dy - dx;
        for (int i = 0; i <= dx; i++){
            grid.set(x0 + i, y, Cell::FREE);
            if (p >= 0){
                y += dir;
                p = p - 2*dx; 
            } 
            p = p + 2*dy; 
        } 
        if (c == 1) {  // Reverting if switched, potential need to fix
            std::swap(x0, x1);
            std::swap(y0, y1);
            
        }
        grid.set(x1, y1, Cell::OBSTRUCTED); // Marking final point obstructed   
    }
}

static void drawLineVertical(Grid2D& grid, int x0, int y0, int x1, int y1) {
    std::cout << "Vertical" << std::endl;
    bool c = 0; //bool variable to tell if the variables have been changed
    if (y0 > y1) {  // If starting point is higher than end flip values
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::cout << "Swapped xy initial with xy final" << std::endl;
        c = 1;
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    int dir; //determining direction of slope
    if (dx < 0){
        dir = -1;
    }
    else{
        dir = 1;
    }
    dx *= dir;

    if (dy != 0){
        int x = x0;
        int p = 2*dx - dy;
        for (int i = 0; i <= dy; i++){
            grid.set(x, y0 + i, Cell::FREE);
            if (p >= 0){
                x += dir;
                p = p - 2*dy; 
            } 
            p = p + 2*dx; 
        } 
        if (c == 1) {  // Reverting if switched, potential need to change
            std::swap(x0, x1);
            std::swap(y0, y1);
            
        }
        grid.set(x1, y1, Cell::OBSTRUCTED); // Marking final point obstructed   
    }
}

void drawLine(Grid2D& grid, int x0, int y0, int x1, int y1) {
    if (std::abs(x1 - x0) > std::abs(y1 - y0))
        drawLineHorizontal(grid, x0, y0, x1, y1);
    else
        drawLineVertical(grid, x0, y0, x1, y1);
}