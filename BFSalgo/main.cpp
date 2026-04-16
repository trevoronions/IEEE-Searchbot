#include "mapping.hpp"
#include "grid.hpp"
#include <iostream>
#include <sstream>
// command to complile g++ -o lidar_map main.cpp grid.cpp mapping.cpp

int main(){
    const int ORIGIN_X = 0; 
    const int ORIGIN_Y = 0;
    const int GRID_W = 20;
    const int GRID_H = 20;
    const float SCALE = 0.05f; // 0.05m resolution, 3 x 3m, 60 x 60 pixels

    Grid2D map(GRID_W, GRID_H);

    drawLine(map, 7, 5, 14, 15);
    drawLine(map, 7, 5, 15, 15);
    map.display();
    return 0;
}






