def dfs(matrix, v):
    global index
    visited[v] = True
    labels[v] = index
    index += 1

    for u in range(n):
        if matrix[v][u] and not visited[u]:
            dfs(matrix, u)


with open("input.txt", "r") as f:
    n = int(f.readline())
    m = []
    for line in f:
        m.append(list(map(int, line.split())))

visited = [False for i in range(n)]
labels = [0 for i in range(n)]
index = 1

for j in range(n):
    if not visited[j]:
        dfs(m, j)
s = ' '.join((map(str, labels)))

with open("output.txt", "w") as fw:
    fw.write(s)
