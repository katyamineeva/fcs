def isPrime(x):
	if x == 1:
		return False
	for i in range(2, int(x ** 0.5) + 2):
		if x % i == 0:
			return False
	return True

def merge(lst1, lst2):
    i1 = 0
    i2 = 0
    lstSorted = []
    while i1 < len(lst1) and i2 < len(lst2):
        if lst1[i1] <= lst2[i2]:
            lstSorted.append(lst1[i1])
            i1 += 1
        else:
            lstSorted.append(lst2[i2])
            i2 += 1
                        
    for i in range(i1, len(lst1)): lstSorted.append(lst1[i])
                
    for i in range(i2, len(lst2)): lstSorted.append(lst2[i])

    return lstSorted
        
        
"""
x = [int(i) for i in input().split()]
print(' '.join(map(str, x)))

x = map(lambda y: y ** 2, x)
print(' '.join(map(str, x)))


x1 = [int(i) for i in input().split()]
x2 = [int(i) for i in input().split()]

print(' '.join(map(str, merge(x1, x2))))
"""

