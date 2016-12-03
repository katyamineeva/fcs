def makeLow(s):
    newS = []
    for letter in s:
        if 'A' <= letter <= 'Z':
            dist = ord('A') - ord('a')
            newLetter = chr(ord(letter) - dist)
            newS.append(newLetter)
        else:
            newS.append(letter)
    return newS
            

def isEqual(s1, s2, i):
    if not i:
        return s1 == s2
    return makeLow(s1) == makeLow(s2)


def transformStr(i):
    if listOfStr == []:
        return []
    else:
        lst = [[listOfStr[0], 1]]
        for ind in range(1, len(listOfStr)):
            if isEqual(listOfStr[ind], lst[-1][0], i):
                lst[-1][1] += 1
            else:
                lst.append([listOfStr[ind], 1])
        return lst

def printS(s, c):
    if c:
        print(str(s[1]) + " " + s[0])
    else:
        print(s[0])




fin = open("input.txt", 'r')

keys = fin.readline()
if keys[-1] == '\n':
    keys = keys[:-1]
keys = keys.split()

c = "-c" in keys
d = "-d" in keys
i = "-i" in keys
u = "-u" in keys

listOfStr = []
s = fin.readline()
while s != '':
    if s[-1] == '\n':
        s = s[:-1]
    listOfStr.append(s)
    s = fin.readline()

listOfStr = transformStr(i)

for s in listOfStr:
    if d and (not u) and s[1] > 1:
        printS(s, c)
    if u and (not d) and s[1] == 1:
        printS(s, c)
    if (not d) and (not u):
        printS(s, c)
        

fin.close()
