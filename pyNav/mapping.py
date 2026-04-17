import math
from dataclasses import dataclass
from grid import Grid2D, Cell

@dataclass
class Point2D:
    x: float
    y: float

def polarToCartesian(r: float, degrees: float) -> Point2D:
    radians = math.radians(degrees)
    return Point2D(r * math.cos(radians), r * math.sin(radians))

def worldToGrid(worldVal: float, scale: float) -> int:
    return round(worldVal / scale)

def drawLineHorizontal(grid: Grid2D, x0: int, y0: int, x1: int, y1: int):
    print("Horizontal")
    c = False
    if x0 > x1:
        x0, x1 = x1, x0
        y0, y1 = y1, y0
        print("Swapped xy initial with xy final")
        c = True
    
    dx = x1 - x0
    dy = y1 - y0
    dir_y = -1 if dy < 0 else 1
    dy = abs(dy)
    
    if dx != 0:
        y = y0
        p = 2 * dy - dx
        for i in range(dx + 1):
            grid.set(x0 + i, y, Cell.FREE)
            if p >= 0:
                y += dir_y
                p -= 2 * dx
            p += 2 * dy
        if c:
            x0, x1 = x1, x0
            y0, y1 = y1, y0
        grid.set(x1, y1, Cell.OBSTRUCTED)

def drawLineVertical(grid: Grid2D, x0: int, y0: int, x1: int, y1: int):
    print("Vertical")
    c = False
    if y0 > y1:
        x0, x1 = x1, x0
        y0, y1 = y1, y0
        print("Swapped xy initial with xy final")
        c = True
    
    dx = x1 - x0
    dy = y1 - y0
    dir_x = -1 if dx < 0 else 1
    dx = abs(dx)
    
    if dy != 0:
        x = x0
        p = 2 * dx - dy
        for i in range(dy + 1):
            grid.set(x, y0 + i, Cell.FREE)
            if p >= 0:
                x += dir_x
                p -= 2 * dy
            p += 2 * dx
        if c:
            x0, x1 = x1, x0
            y0, y1 = y1, y0
        grid.set(x1, y1, Cell.OBSTRUCTED)

def drawLine(grid: Grid2D, x0: int, y0: int, x1: int, y1: int):
    if abs(x1 - x0) > abs(y1 - y0):
        drawLineHorizontal(grid, x0, y0, x1, y1)
    else:
        drawLineVertical(grid, x0, y0, x1, y1)