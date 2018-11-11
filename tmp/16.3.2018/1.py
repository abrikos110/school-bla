n, m = map(int, input().split())

ans = [[None for i in range(m)] for j in range(n)]

def get(i, j):
    global ans
    if i not in range(n) or j not in range(m):
        return 0
    if ans[i][j] != None:
        return ans[i][j]
    ans[i][j] = get(i+1, j) + get(i, j+1)
    return ans[i][j]

ans[-1][-1] = 1
print(get(0, 0))

raise SystemExit

for bla in ans:
    print(*bla, sep='\t')

