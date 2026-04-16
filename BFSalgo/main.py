from pyNav.mapping import Grid2D, drawLine

ORIGIN_X = 0
ORIGIN_Y = 0
GRID_W = 20
GRID_H = 20
SCALE = 0.05  # 0.05m resolution, 3 x 3m, 60 x 60 pixels

map_grid = Grid2D(GRID_W, GRID_H)

drawLine(map_grid, 7, 5, 14, 15)
drawLine(map_grid, 7, 5, 15, 15)
map_grid.display()