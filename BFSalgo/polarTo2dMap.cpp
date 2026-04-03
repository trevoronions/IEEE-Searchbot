#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

enum class Cell : int{ 
    UNKNOWN = 0, 
    FREE = 1,
    OBSTRUCTED = 2
};
struct Grid2D {
    int width, height;
    std::vector<std::vector<Cell>> cells;

    Grid2D(int w, int h, Cell defaultCell = Cell::UNKNOWN)
        : width(w), height(h),
          cells(h, std::vector<Cell>(w, defaultCell)) {}

    void set(int x, int y, Cell value) {
        if (inBounds(x, y)) cells[y][x] = value;
    }

    Cell get(int x, int y) const {
        if (inBounds(x, y)) return cells[y][x];
        return Cell::UNKNOWN;
    }

    bool inBounds(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    void display() const {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                switch (cells[y][x]) {
                    case Cell::FREE:        std::cout << ". "; break;
                    case Cell::OBSTRUCTED:  std::cout << "# "; break;
                    case Cell::UNKNOWN:     std::cout << "? "; break;
                }
            }
            std::cout << '\n';
        }
    }
};
void polarToCartesian(float r, float degrees, float& x, float& y)
{
    float radians = degrees * (M_PI / 180.0);
    x = r * cos(radians);
    y = r * sin(radians);
}

void drawLineHorizontal(Grid2D& grid, int x0, int y0, int  x1, int y1){
    std::cout << "Horizontal" << std::endl;
    grid.set(x1, y1, Cell::OBSTRUCTED); // Marking final point obstructed   

    if (x0 > x1) {  // If starting point is higher than end flip values
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::cout << "Swapped xy initial with xy final" << std::endl; // Testing
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
        for (int i = 0; i < dx; i++){
            grid.set(x0 + i, y, Cell::FREE);
            if (p >= 0){
                y += dir;
                p = p - 2*dx; 
            } 
            p = p + 2*dy; 
        } 
    }
    
}
void drawLineVertical(Grid2D& grid, int x0, int y0, int  x1, int y1){ // Copy of drawLineHorizontal if the slope is more vertical than horizontal 
    std::cout << "Vertical" << std::endl;
    grid.set(x1, y1, Cell::OBSTRUCTED); // Marking final point obstructed   

    if (y0 > y1) {  // If starting point is higher than end flip values
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::cout << "Swapped xy initial with xy final" << std::endl;
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
        for (int i = 0; i < dy; i++){
            grid.set(x, y0 + i, Cell::FREE);
            if (p >= 0){
                x += dir;
                p = p - 2*dy; 
            } 
            p = p + 2*dx; 
        } 
    }
}

void drawLine(Grid2D& grid, int x0, int y0, int x1, int y1) // Bresenham's line algo
{
    if (std::abs(x1-x0) > abs(y1-y0)){
        drawLineHorizontal(grid, x0, y0, x1, y1);
    }
    else {
        drawLineVertical(grid, x0, y0, x1, y1);
    }
}