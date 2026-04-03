#include "implementation.cpp"
using namespace std; 

/* 
outputs two graphs, first shows results of BFS, tracking arrows from Z to A you find
the shortest path. Second graph shows that shortest path
*/
int main() {
  float resolution = 0.05f; // 5 cm per cell, 60x60 grid, 3mx3m map size
  GridLocation start{17, 2}, goal{19, 9};
  SquareGrid grid = make_diagram1();
  auto came_from = breadth_first_search(grid, start, goal);
  draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
  cout << '\n';
  vector<GridLocation> path = reconstruct_path(start, goal, came_from);
  draw_grid(grid, nullptr, nullptr, &path, &start, &goal);

  return 0;
}