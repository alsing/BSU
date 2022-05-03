from collections import deque


def bfs(n, matrix):
    q = deque()
    visited = [False for i in range(n)]
    labels = [0 for i in range(n)]

    visited[0] = True
    labels[0] = 1
    q.append(0)
    i = 2

    for j in range(n):
        if not q and not visited[j]:
            visited[j] = True
            labels[j] = i
            q.append(j)
            i += 1

        while q:
            v = q.popleft()
            for u in range(n):
                if matrix[v][u] and not visited[u]:
                    visited[u] = True
                    labels[u] = i
                    q.append(u)
                    i += 1

    return labels


with open("input.txt", "r") as f:
    n = int(f.readline())
    m = []
    for line in f:
        m.append(list(map(int, line.split())))

l = bfs(n, m)
s = ' '.join((map(str, l)))

with open("output.txt", "w") as fw:
    fw.write(s)
