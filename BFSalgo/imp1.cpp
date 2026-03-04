#include "implementation.cpp"
using namespace std;

struct GridLocation {
  int x, y;
};

struct SimpleGraph {
  unordered_map<char, vector<char> > edges;

  vector<char> neighbors(char id) {
    return edges[id];
  }
};

struct SquareGrid {
  static array<GridLocation, 4> DIRS;

  int width, height;
  unordered_set<GridLocation> walls;

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const {
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
  }

  bool passable(GridLocation id) const {
    return walls.find(id) == walls.end();
  }

  vector<GridLocation> neighbors(GridLocation id) const {
    vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (in_bounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      // see "Ugly paths" section for an explanation:
      reverse(results.begin(), results.end());
    }

    return results;
  }
};

// Helpers for GridLocation

bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
  return tie(a.x, a.y) < tie(b.x, b.y);
}

basic_iostream<char>::basic_ostream& operator<<(basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}


// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class Graph>
void draw_grid(const Graph& graph,
               unordered_map<GridLocation, double>* distances=nullptr,
               unordered_map<GridLocation, GridLocation>* point_to=nullptr,
               vector<GridLocation>* path=nullptr,
               GridLocation* start=nullptr,
               GridLocation* goal=nullptr) {
  const int field_width = 3;
  cout << string(field_width * graph.width, '_') << '\n';
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      GridLocation id {x, y};
      if (graph.walls.find(id) != graph.walls.end()) {
        cout << string(field_width, '#');
      } else if (start && id == *start) {
        cout << " A ";
      } else if (goal && id == *goal) {
        cout << " Z ";
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        cout << " @ ";
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) { cout << " > "; }
        else if (next.x == x - 1) { cout << " < "; }
        else if (next.y == y + 1) { cout << " v "; }
        else if (next.y == y - 1) { cout << " ^ "; }
        else { cout << " * "; }
      } else if (distances != nullptr && distances->count(id)) {
        cout << ' ' << left << setw(field_width - 1) << (*distances)[id];
      } else {
        cout << " . ";
      }
    }
    cout << '\n';
  }
  cout << string(field_width * graph.width, '~') << '\n';
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



