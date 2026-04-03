#include "polarTo2dMap.cpp"
int main(){
    Grid2D grid(20, 20); // 0.05m resolution, 3 x 3m, 60 x 60 pixels


    drawLine(grid, 3, 3, 10, 3);
    drawLine(grid, 7, 5, 15, 15);
    grid.display();
    return 0;
}






