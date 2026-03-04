#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
using namespace std; 

struct GridLocation {
  int x, y;
};

// Helpers for GridLocation

bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
template <> struct hash<GridLocation> {
  std::size_t operator()(const GridLocation& id) const noexcept {
    // I wish built-in std::hash worked on pair and tuple
    return std::hash<int>()(id.x ^ (id.y << 16));
  }
};
}


struct SquareGrid {
  static std::array<GridLocation, 4> DIRS;

  int width, height;
  std::unordered_set<GridLocation> walls;

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const {
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
  }

  bool passable(GridLocation id) const {
    return walls.find(id) == walls.end();
  }

  std::vector<GridLocation> neighbors(GridLocation id) const {
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (in_bounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      // see "Ugly paths" section for an explanation:
      std::reverse(results.begin(), results.end());
    }

    return results;
  }
};

std::array<GridLocation, 4> SquareGrid::DIRS = {
  /* East, West, North, South */
  GridLocation{1, 0}, GridLocation{-1, 0},
  GridLocation{0, -1}, GridLocation{0, 1}
};
template<typename Location, typename Graph>
std::unordered_map<Location, Location>
breadth_first_search(Graph graph, Location start) {
  std::queue<Location> frontier;
  frontier.push(start);

  std::unordered_map<Location, Location> came_from;
  came_from[start] = start;

  while (!frontier.empty()) {
    Location current = frontier.front();
    frontier.pop();

    for (Location next : graph.neighbors(current)) {
      if (came_from.find(next) == came_from.end()) {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
  return came_from;
}

template<typename Location, typename Graph>
unordered_map<Location, Location>
breadth_first_search(Graph graph, Location start, Location goal) {
  queue<Location> frontier; //defining frontier as a queue data struct
  frontier.push(start);

  unordered_map<Location, Location> came_from;
  came_from[start] = start;

  while (!frontier.empty()) {
    Location current = frontier.front(); //assigning top of frontier to current
    frontier.pop(); //removes first element


    if (current == goal) {
      break;
    }
    
    for (Location next : graph.neighbors(current)) {
      if (came_from.find(next) == came_from.end()) {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
  return came_from;
}
void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(GridLocation{x, y});
    }
  }
}

SquareGrid make_diagram1() {
  SquareGrid grid(30, 15);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}

template<class Graph>
void draw_grid(const Graph& graph,
               std::unordered_map<GridLocation, double>* distances=nullptr,
               std::unordered_map<GridLocation, GridLocation>* point_to=nullptr,
               std::vector<GridLocation>* path=nullptr,
               GridLocation* start=nullptr,
               GridLocation* goal=nullptr) {
  const int field_width = 3;
  std::cout << std::string(field_width * graph.width, '_') << '\n';
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      GridLocation id {x, y};
      if (graph.walls.find(id) != graph.walls.end()) {
        std::cout << std::string(field_width, '#');
      } else if (start && id == *start) {
        std::cout << " A ";
      } else if (goal && id == *goal) {
        std::cout << " Z ";
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        std::cout << " @ ";
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) { std::cout << " > "; }
        else if (next.x == x - 1) { std::cout << " < "; }
        else if (next.y == y + 1) { std::cout << " v "; }
        else if (next.y == y - 1) { std::cout << " ^ "; }
        else { std::cout << " * "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
      } else {
        std::cout << " . ";
      }
    }
    std::cout << '\n';
  }
  std::cout << std::string(field_width * graph.width, '~') << '\n';
}


template<typename Location>
std::vector<Location> reconstruct_path(
   Location start, Location goal,
   std::unordered_map<Location, Location> came_from
) {
  std::vector<Location> path;
  Location current = goal;
  if (came_from.find(goal) == came_from.end()) {
    return path; // no path can be found
  }
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}
