import heapq

with open("huffman.in", "r") as f:
    n = int(f.readline())
    q = list(map(int, f.readline().split()))
    heapq.heapify(q)

s = 0
while len(q) > 1:
    el = heapq.heappop(q)
    el += heapq.heappop(q)
    heapq.heappush(q, el)
    s += el

with open("huffman.out", "w") as fw:
    fw.write(str(s))
