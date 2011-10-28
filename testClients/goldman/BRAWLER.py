import operator
import random
import sys
import copy

functions = {"add" : operator.add,
             "sub" : operator.sub,
             "mul" : operator.mul,
             "div" : lambda X, Y: float(X) / Y if Y != 0 else X / 0.00001}

moveValues = ["openSpace",
              "enemySpace",
              "friend!=",
              "friend=",
              "enemy<",
              "enemy>",
              "enemy=",
              ]

spawnValues = ["enemy<",
               "enemy=",
               "enemy>",
               "friend<",
               "friend=",
               "friend>",
               ]

class Leaf(object):
    def __init__(self, values, key=None):
        if key is None:
            self.key = random.choice(values)
        else:
            self.key = key
    def cross(self, other):
        return

    def __str__(self):
        return self.key

    def eval(self, lookup):
        try:
            return lookup[self.key]
        except:
            print self.key
            print lookup
            print lookup[self.key]

class Internal(object):
    def __init__(self, depth, builder, values, function=None):
        if function is None:
            self.function = random.choice(functions.items())
        else:
            self.function = function
        self.left = builder(depth - 1, values)
        self.right = builder(depth - 1, values)

    def cross(self, other):
        if not isinstance(other, Internal):
            return
        if random.randint(0, 1) == 1:
            self.left, other.left = other.left, self.left
            self.right.cross(other.right)
        else:
            self.right, other.right = other.right, self.right
            self.left.cross(other.left)

    def __str__(self):
        return "%s %s %s" % (self.function[0], str(self.left), str(self.right))

    def eval(self, lookup):
        return self.function[1](self.left.eval(lookup), self.right.eval(lookup))

class Individual(object):
    def __init__(self, builder, depth=0, fitness=0, plays=0):
        self.move = builder(depth, moveValues)
        self.spawn = builder(depth, spawnValues)
        self.fitness = fitness
        self.plays = plays

    def resetFitness(self):
        self.fitness = 0
        self.plays = 0

    def compressFitness(self):
        if self.plays != 0:
            self.fitness /= self.plays
            self.plays = 1

    def cross(self, other):
        c1, c2 = copy.deepcopy(self), copy.deepcopy(other)
        c1.resetFitness()
        c2.resetFitness()
        c1.move, c2.move = c2.move, c1.move
        c1.move.cross(c2.move)
        c1.spawn.cross(c2.spawn)

        return c1, c2

    def __cmp__(self, other):
        return 1 if self.fitness > other.fitness else -1 if self.fitness < other.fitness else 0

    def __str__(self):
        return "%f %i %s %s\n" % (self.fitness, self.plays, str(self.move), str(self.spawn))

def full(depth, values):
    if depth > 0:
        return Internal(depth, full, values)
    else:
        return Leaf(values)

def halfnhalf(depth, values):
    if depth > 0 and random.random() < 0.5:
        return Internal(depth, halfnhalf, values)
    else:
        return Leaf(values)

def fullnhalf(depth, values):
    if depth > 0:
        return Internal(depth, halfnhalf, values)
    else:
        return Leaf(values)


def buildFromString(raw):
    data = list(reversed(raw.split(' ')))
    fitness = float(data.pop())
    plays = int(data.pop())
    def builder(_, values):
        current = data.pop()
        if current in functions:
            return Internal(0, builder, values, (current, functions[current]))
        else:
            return Leaf(values, current)
    return Individual(builder, fitness=fitness, plays=plays)

def load(file):
    with open(file, 'r') as f:
        raw = f.read().split('\n')
    return [buildFromString(text) for text in raw if len(text) > 0]

def save(file, pop):
    with open(file, 'w') as f:
        for individual in pop:
            f.write(str(individual))

def getNext(file):
    popSize = 12
    repeats = 3
    depth = 10
    method = fullnhalf
    try:
        pop = load(file)
    except:
        pop = [Individual(method, depth) for _ in range(popSize)]
    toEval = filter(lambda X: X.plays < repeats, pop)
    if len(toEval) == 0:
        pop.sort(reverse=True)
        midway = len(pop) / 2
        for i in range(0, midway, 2):
            pop[midway + i], pop[midway + i + 1] = pop[i].cross(pop[i + 1])
        for individual in pop:
            individual.compressFitness()
        toEval = pop
    return pop, random.choice(toEval)
