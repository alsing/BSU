class DisjointSetUnion:
    def __init__(self, n):
        self.size = [1 for i in range(n)]
        self.parent = [i for i in range(n)]
        self.components = n

    def FindSet(self, x):
        if x == self.parent[x]:
            return x
        self.parent[x] = self.FindSet(self.parent[x])
        return self.parent[x]

    def Union(self, x, y):
        x = self.FindSet(x)
        y = self.FindSet(y)
        if x != y:
            if self.size[x] < self.size[y]:
                x, y = y, x
            self.parent[y] = x
            self.size[x] += self.size[y]
            self.components -= 1


with open("input.txt", "r") as f:
    n, q = list(map(int, f.readline().split()))
    roads = []
    for line in f:
        roads.append(list(map(int, line.split())))

dsu = DisjointSetUnion(n)

with open("output.txt", "w") as fw:
    for road in roads:
        dsu.Union(road[0] - 1, road[1] - 1)
        fw.writelines(str(dsu.components) + '\n')
