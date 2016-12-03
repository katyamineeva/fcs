hights = [int(i) for i in input().split()]
hights.sort()
hights.reverse()
peterHight = int(input())

ind = 0
while (ind < len(hights)) and (peterHight <= hights[ind]):
    ind += 1

print(str(ind + 1))
