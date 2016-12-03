fin = open("input.txt", 'r')
fout = open("output.txt", 'w')

dic = {}
s = fin.readline()
while s != "\n" and s != "":
    s = s.split('\t')
    verdict = s[-1]
    langName = s[-2]
    if verdict == "OK\n" or verdict == "OK":
        dic.setdefault(langName, 0)
        dic[langName] += 1
    s = fin.readline()


ans = []
for key in dic:
    ans.append((-dic[key], key))

ans.sort()
for i in ans:
    print(i[1] + ' ' + str(-i[0]))

fin.close()
fout.close()
