from collections import deque

def bfs(start, finish):
    used = [False for i in range(n)]
    queue = deque([[start, 0]])
    used[start] = True
    depth = 0
    
    print(queue)
    
    cur = queue.pop()
    while cur[0] != finish:
        for ver in graph[cur[0]]:
            if not used[ver]:
                queue.appendleft([ver, cur[1] + 1])
                used[ver] = True
        
        cur = queue.pop()
    
    cnt = 1
    depth = cur[1]
    for i in queue:
        if i == cur:
            cnt += 1
        
    return cnt
        
    
    
finput = open("input.txt", "r")
foutput = open("output.txt", "w")

n, m = map(int, finput.readline().split())
start, finish = map(int, finput.readline().split())
start -= 1
finish -= 1

graph = [[] for i in range(n)]

for i in range(m):
    v, u = map(int, finput.readline().split())
    graph[v - 1].append(u - 1)
    graph[u - 1].append(v - 1)
    

## used = [False for i in range(n)]
ans = bfs(start, finish)
print(ans)        

finput.close()
foutput.close()