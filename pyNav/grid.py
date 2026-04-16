from enum import IntEnum

class Cell(IntEnum):
    UNKNOWN = 0
    FREE = 1
    OBSTRUCTED = 2

class Grid2D:
    def __init__(self, width: int, height: int, defaultCell: Cell = Cell.UNKNOWN):
        self.width = width
        self.height = height
        self.cells = [[defaultCell for _ in range(width)] for _ in range(height)]

    def set(self, x: int, y: int, value: Cell):
        if self.inBounds(x, y):
            self.cells[y][x] = value

    def get(self, x: int, y: int) -> Cell:
        if self.inBounds(x, y):
            return self.cells[y][x]
        return Cell.UNKNOWN

    def inBounds(self, x: int, y: int) -> bool:
        return 0 <= x < self.width and 0 <= y < self.height

    def display(self):
        for row in self.cells:
            for cell in row:
                if cell == Cell.FREE:
                    print('. ', end='')
                elif cell == Cell.OBSTRUCTED:
                    print('# ', end='')
                else:
                    print('? ', end='')
            print()