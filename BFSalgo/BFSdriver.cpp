#include "implementation.cpp"
using namespace std; 

/* 
outputs two graphs, first shows results of BFS, tracking arrows from Z to A you find
the shortest path. Second graph shows that shortest path
*/
int main() {
  GridLocation start{8, 7}, goal{17, 2};
  SquareGrid grid = make_diagram1();
  auto came_from = breadth_first_search(grid, start, goal);
  draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
  cout << '\n';
  vector<GridLocation> path = reconstruct_path(start, goal, came_from);
  draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
}