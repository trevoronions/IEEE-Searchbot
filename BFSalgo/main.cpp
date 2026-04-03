#include "mapping.hpp"
#include "grid.hpp"
#include <iostream>
#include <sstream>


int main(){
    const int ORIGIN_X = 0; 
    const int ORIGIN_Y = 0;
    const int GRID_W = 60;
    const int GRID_H = 60;
    const float SCALE = 0.05f; // 0.05m resolution, 3 x 3m, 60 x 60 pixels

    Grid2D map(GRID_W, GRID_H);

    drawLine(map, 10, 3, 3, 3);
    drawLine(map, 7, 5, 15, 15);
    map.display();
    return 0;
}






