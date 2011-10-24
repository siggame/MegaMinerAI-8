import random
def ymirror(x, y, width, height):
    return (width - x - 1, y)

def xmirror(x, y, width, height):
    return (x, height - y - 1)

def rotate(x, y, width, height):
    return (width - x - 1, height - y - 1)

def dist(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

class Map(object):
    def __init__(self, width, height, sym, maxWalls):
        self.width = width
        self.height = height
        self.sym = sym
        self.maxWalls = maxWalls


        self.edges = [(0, y) for y in range(1, self.height - 1)] + [(self.width - 1, y) for y in range(1, self.height - 1)] + \
                     [(x, 0) for x in range(1, self.width - 1)] + [(x, height - 1) for x in range(1, self.width - 1)]
        self.offsets = [(x, y) for x in [-1, 0, 1] for y in [-1, 0, 1] if x != 0 or y != 0]
        self.generate()

    def center(self, current):
        maxDistance = self.width + self.height
        cx, cy, count = 0.0, 0.0, 0.0
        for x in range(self.width):
            for y in range(self.height):
                if self.get(x, y) == 'X':
                    cx += maxDistance - abs(x - current[0])
                    cy += maxDistance - abs(y - current[1])

        return self.unitValue(cx), self.unitValue(cy)

    def unitValue(self, value):
        if value == 0:
            return 0
        elif value < 0:
            return -1
        else:
            return 1

    def getOffset(self, current):
        center = self.center()
        return self.unitValue(current[0], center[0]), self.unitValue(current[1], center[1])

    def draw(self):
        x, y = random.choice(self.edges)
        dx, dy = random.choice([(dx, dy) for (dx, dy) in self.offsets if 0 < x + dx < self.width - 1 and 0 < y + dy < self.height - 1])
        while True:
            #if random.random() < 0.75:
            self.set(x, y, 'X')
            x += dx
            y += dy
            if not (0 <= x < self.width) or not (0 <= y < self.height):
                break;

    def generate(self):
        self.side = [['.'] * self.height for _ in range(self.width)]
        self.wallCount = 0
        for _ in range(self.maxWalls):
            self.draw()

        options = [(x, y) for x in range(self.width) for y in range(self.height)]
        bases = []
        for _ in range(3):
            while True:
                choose = random.choice(options)
                if self.get(choose[0], choose[1]) == '.':
                    break
            self.set(choose[0], choose[1], '0')
            bases.append(choose)

        self.ensureConnect(bases)


    def ensureConnect(self, open):
        mystery = set((x, y) for x in range(self.width) for y in range(self.height) if self.get(x, y) != 'X')
        possibleWalls = set((x, y) for x in range(self.width) for y in range(self.height) if self.get(x, y) == 'X')
        walls = []
        for base in open:
            mystery.remove(base)
        while len(mystery) > 0:
            if len(open) == 0:
                distances = [(dist(wall, goal), wall) for wall in walls for goal in mystery]
                random.shuffle(distances)
                wall = min(distances)[1]
                mirror = self.sym(wall[0], wall[1], self.width, self.height)
                self.set(wall[0], wall[1], '.')
                open.append(wall)
            working = open.pop()
            for offset in [(0, 1), (1, 0), (-1, 0), (0, -1)]:
                next = working[0] + offset[0], working[1] + offset[1]
                if next in mystery:
                    mystery.remove(next)
                    if self.get(*next) != '1':
                        open.append(next)
                elif next in possibleWalls:
                    possibleWalls.remove(next)
                    walls.append(next)

    def get(self, x, y):
        return self.side[x][y]

    def set(self, x, y, value):
        self.side[x][y] = value
        x, y = self.sym(x, y, self.width, self.height)
        value = '1' if value == '0' else '0' if value == '1' else value
        self.side[x][y] = value

    def __str__(self):
        return '\n'.join([' '.join([self.get(x, y) for x in range(self.width)]) for y in range(self.height)]) + '\n'

map = Map(40, 20, random.choice([ymirror, xmirror, rotate]), 4)
#map.set(2, 1, 'X')
print str(map)

