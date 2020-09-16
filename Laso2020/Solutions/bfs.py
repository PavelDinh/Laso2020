f = open('graph.txt', 'r')
n,m = f.readline().split()
m = int(m)
n = int(n)

adj = []
for i in range(n): adj.append([])

for i in range(m):
    line = f.readline().split()
    u = int(line[0])
    v = int(line[1])
    adj[u].append(v)
    adj[v].append(u)


def BFS(s :int):
    queue = []
    queue.append(s)
    dist = {}
    dist[s] = 0

    while len(queue) != 0:
        v = queue.pop(0)
        for w in adj[v]:
            if not (w in dist):
                dist[w] = dist[v] + 1
                queue.append(w)

    return dist

dist = BFS(0)
print(dist[7])
print(len(dist))