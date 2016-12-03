fin = open("input.txt", "r")
fout = open("output.txt", "w")

text = []
s = fin.readline()

while s != "\n" and s != "":
    
    for i in s.split():
        text.append(i)
    s = fin.readline()

dic = {}

for i in text:
    dic.setdefault(i, 0)
    dic[i] += 1

maxValue = max(dic.values())

ans = []
for i in dic:
    if dic[i] == maxValue:
        ans.append(i)

ans.sort()
print(ans[0])

fin.close()
fout.close()
