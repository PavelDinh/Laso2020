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


def DFS(s :int):
    queue = []
    queue.append(s)
    visited = {}
    visited[s] = True

    while len(queue) != 0:
        v = queue.pop(-1)
        for w in adj[v]:
            if not (w in visited):
                visited[w] = True
                queue.append(w)

    return visited

visited = DFS(0)
print(len(visited))