from queue import PriorityQueue

with open("huffman.in", "r") as f:
    n = int(f.readline())
    q = PriorityQueue(n)
    for i in f.readline().split():
        q.put(int(i))

s = 0
while q.qsize() > 1:
    el = q.get()
    el += q.get()
    q.put(el)
    s += el

with open("huffman.out", "w") as fw:
    fw.write(str(s))
