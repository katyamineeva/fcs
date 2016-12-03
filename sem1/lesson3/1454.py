a1 = [int(x) for x in input().split()]
s1 = set(a1)

a2 = [int(x) for x in input().split()]
s2 = set(a2)

s3 = s1 & s2
print(len(s3))

