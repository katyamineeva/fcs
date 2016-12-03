fin = open("data.txt", 'r')
s = fin.read()
fin.close()

s2 = ""
for i in range(len(s)):
    if s[i] == '.':
        s2 += ','
    else:
        s2 += s[i]

fout = open("data.txt", 'w')
fout.write(s2)
fout.close()
