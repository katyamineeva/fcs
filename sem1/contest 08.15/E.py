def binsearch(p, length):
    left = 0
    right = length
    while (right - left > 1):
        mid = (left + right) // 2
##        print("left = ", left, ", right = ", right, ", mid = ", mid, ", coll[mid] = ", collection[mid])
        if collection[mid] == p:
            ans = max(0, mid)
            return ans
        elif (collection[mid] < p):
            left = mid
        else:
            right = mid
    ans = left + 1
    return ans

finput = open("input.txt", "r")
foutput = open("output.txt", "w")


n = int(finput.readline())
a = [int(x) for x in finput.readline().split()]
a.sort()

if (n > 0):
    collection = [a[0]]
    
for i in range(1, n):
    if collection[-1] != a[i]:
        collection.append(a[i])

length = len(collection)
##print(collection)

k = int(finput.readline())
p = [int(x) for x in finput.readline().split()]
for i in range(k):
    if collection[0] >= p[i]:
        foutput.write("0\n")
    else:
        ans = binsearch(p[i], length)
        foutput.write(str(ans) + "\n")

finput.close()
foutput.close() 