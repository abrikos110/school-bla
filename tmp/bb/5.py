a, b = map(int, input().split())
print(*(a + (b-a)*k for k in range(int(input('N: ')))))
