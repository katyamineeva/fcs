lst = [int(x) for x in input().split()]
lst = [lst[-1]] + lst[:-1]
print(' '.join(map(str, lst)))
