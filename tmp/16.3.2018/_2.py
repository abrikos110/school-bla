from functools import lru_cache


def C(n, k):
    if k < 0 or n < 0:
        return 0
    if k == 0 or n == k:
        return 1
    return C(n-1, k-1) + C(n-1, k)


n, m = map(int, input().split())

print(C(max(n, m), min(n, m)))

