password = input()
variants = []

maxNumOfA = 0
maxNumOf0 = 0
for i in password:
    if i == 'a':
        maxNumOfA += 1
    if i == 'o':
        maxNumOf0 += 1
        

for maskA in range(1, 2 ** maxNumOfA):
    for mask0 in range(1, 2 ** maxNumOf0):
        cntA = 0
        cnt0 = 0
        newPassword = ""
        for i in password:
            if i != 'a' and i != 'o':
                newPassword += i
            if i == 'a':
                if (maskA & (1 << cntA)) >> cntA == 1:
                    newPassword += 'A'
                else:
                    newPassword += 'a'
                cntA += 1
            if i == 'o':
                if (mask0 & (1 << cnt0)) >> cnt0 == 1:
                    newPassword += '0'
                else:
                    newPassword += 'o'
                cnt0 += 1
        variants.append(newPassword)

variants.sort()

start = 1
for i in password:
    if i != 'a' and i != 'o':
        start = 0

end = len(variants)
for i in range(start, end):
    print(variants[i])