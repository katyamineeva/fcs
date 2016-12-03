fin = open("input.txt", "r")
fout = open("output.txt", "w")

text = []
s = fin.readline()

while s != "\n" and s != "":
    
    for i in s.split():
        text.append(i)
    s = fin.readline()

dic = {}
ans = []
for i in text:
    ans.append(dic.setdefault(i, 0))
    dic[i] += 1

print(' '.join(map(str, ans)))
    
fin.close()
fout.close()
