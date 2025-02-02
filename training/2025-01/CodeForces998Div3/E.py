def solve():
    import sys
    data = sys.stdin.read().strip().split()
    idx = 0
    
    n = int(data[idx]); idx += 1
    m1 = int(data[idx]); idx += 1
    m2 = int(data[idx]); idx += 1
    
    F = []
    G = []
    FSet = [i for i in range(n+1)]
    GSet = [i for i in range(n+1)]
    
    def find(S, x):
        if S[x] != x:
            S[x] = find(S, S[x])
        return S[x]
    
    def merge(S, x, y):
        rx = find(S, x)
        ry = find(S, y)
        if rx != ry:
            S[rx] = ry
    
    for i in range(m1):
        u = int(data[idx]); idx += 1
        v = int(data[idx]); idx += 1
        F.append((u, v))
    
    for i in range(m2):
        u = int(data[idx]); idx += 1
        v = int(data[idx]); idx += 1
        merge(GSet, u, v)
        G.append((u, v))
    
    for (u, v) in F:
        # ...existing code continues...
        pass