s1 = set([int(x) for x in input().split()])
s2 = set([int(x) for x in input().split()])
s = [x for x in (s1 & s2)]
s.sort()
print(' '.join(map(str, s)))
