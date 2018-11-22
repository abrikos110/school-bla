#!/usr/bin/python

import decimal

ctx = decimal.getcontext()
ctx.prec = 10000
decimal.setcontext(ctx)

def sqrt(x):
    D = decimal.Decimal
    ans = D(x)
    lans = -4
    while lans != ans:
        lans = ans
        ans = (ans + D(x)/ans)/2
    return ans

def over_golden_phi_hash(data, N, phi=(sqrt(5)-1)/2):
    ans = 0
    p = 1
    for i in range(len(data)):
        ans += data[i] * p
        p *= 256
    return int((ans * phi) % 1 * N)

def polynomial_hash(data, p=127, q=10**9+7):
    ans = 0
    pw = 1
    for i in data:
        ans = (ans + pw*i) % q
        pw *= p
    return ans

