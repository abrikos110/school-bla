from functools import lru_cache



def C(n, k):
    if n == 0 or n == k:
        return 1
    return C(n-1, k-1) + C(n-1, k)



