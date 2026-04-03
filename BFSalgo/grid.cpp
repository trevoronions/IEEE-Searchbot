#include "grid.hpp"

Grid2D::Grid2D(int w, int h, Cell defaultCell)
    : width(w), height(h),
        cells(h, std::vector<Cell>(w, defaultCell)) {}

void Grid2D::set(int x, int y, Cell value) {
    if (inBounds(x, y)) cells[y][x] = value;
}

Cell Grid2D::get(int x, int y) const {
    if (inBounds(x, y)) return cells[y][x];
    return Cell::UNKNOWN;
}

bool Grid2D::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Grid2D::display() const {
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