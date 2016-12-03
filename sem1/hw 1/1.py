fin = open("input.txt", 'r')
fout = open("output.py", 'w')

painted = set()
position = [0, 0]

actions = []
s = fin.readline()
while s != '':
    if s != '\n':
        if s[-1] == '\n':
            actions.append(s[:-1])
        else:
            actions.append(s)
    s = fin.readline()


code = []
cntNum = 0
for st in actions:
    cntSp = 0
    while cntSp < len(st) and st[cntSp] == ' ':
        cntSp += 1
    s = st.split()
    if s[0] == "up":
        code.append(' ' * cntSp + "position[1] += 1")
    elif s[0] == "left":
        code.append(' ' * cntSp + "position[0] -= 1")
    elif s[0] == "down":
        code.append(' ' * cntSp + "position[1] -= 1")
    elif s[0] == "right":
        code.append(' ' * cntSp + "position[0] += 1")
    elif s[0] == "paint":
        code.append(' ' * cntSp + "painted.add((position[0], position[1]))")
    else:    
        n = int(s[0])
        cntName = "i" + str(cntNum)
        cntNum += 1
        code.append(' ' * cntSp + "for " + cntName + " in range(" + str(n) + "):")


code = '\n'.join(code)       
exec(code)
print(len(painted))

fin.close()
fout.close()
