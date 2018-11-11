import random as rnd


p = {}

def connect(p, a. b):
    if rnd.random() > 0.5:
        p[a] = p[b]
        cur = a
    else:
        p[b] = p[a]
        cur = b
    c = cur
    while p[c] is not None:
        c = p[c]
    a = c
    while p[cur] is not None:
        c = cur
        cur = p[cur]
        p[c] = a


n = int(input())
for i in range(n):
    a, b = input().split()
    if a not in p: p[a] = None
    if b not in p: p[b] = None
    connect(p, a, b)

word = int(input())

    


