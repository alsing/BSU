import numpy as np


class Hackers:
    def __init__(self, filename: str):
        self.order_labels = []
        self.n_components = 0
        with open(filename, "r") as f:
            self.n = int(f.readline())
            self.adjacency_list = [[] for i in range(self.n)]
            self.reversed_adjacency_list = [[] for i in range(self.n)]
            self.visited = [False for i in range(self.n)]
            self.in_component = [-1 for i in range(self.n)]
            self.terminals = []
            for i in range(self.n):
                self.terminals.append(int(f.readline()))
            for line in f:
                if line[0] != '0':
                    u, v = map(int, line.split())
                    self.adjacency_list[u - 1].append(v - 1)
                    self.reversed_adjacency_list[v - 1].append(u - 1)

    def dfs(self, v):
        if self.visited[v]:
            return
        self.visited[v] = True
        for u in self.adjacency_list[v]:
            if not self.visited[u]:
                self.dfs(u)
        self.order_labels.append(v)

    def reversed_dfs(self, v):
        if self.visited[v]:
            return
        self.visited[v] = True
        self.in_component[v] = self.n_components
        for u in self.reversed_adjacency_list[v]:
            if not self.visited[u]:
                self.reversed_dfs(u)

    def solve(self):
        for u in range(self.n):
            self.dfs(u)
        self.visited = [False for i in range(self.n)]
        self.order_labels.reverse()
        for u in self.order_labels:
            if self.in_component[u] == -1:
                self.reversed_dfs(u)
                self.n_components += 1
        min_terminals = [-1 for i in range(self.n_components)]
        for i in range(self.n_components):
            min_terminal = np.inf
            for j in range(len(self.in_component)):
                if self.in_component[j] == i and self.terminals[j] < min_terminal:
                    min_terminal = self.terminals[j]
                    min_terminals[i] = j
        self.visited = [False for i in range(self.n)]
        self.order_labels.clear()
        machines_to_capture = []
        for u in min_terminals:
            if not self.visited[u]:
                machines_to_capture.append(u + 1)
                self.dfs(u)
        return machines_to_capture


hackers = Hackers('input.txt')
solution = hackers.solve()
s = ' '.join((map(str, solution)))
with open("output.txt", "w") as fw:
    fw.write(str(len(solution)))
    fw.write('\n')
    fw.write(s)
