def f(ind, cnt0):
    while ind < len(actions) and actions[ind][:cnt0] == ' ' * cnt0 and actions[ind][cnt0] != ' ':
        command = actions[ind][cnt0:]
        if command == "left":
            position[0] -= 1
        elif command == "right":
            position[0] += 1
        elif command == "up":
            position[1] += 1
        elif command == "down":
            position[1] -= 1
        elif command == "paint":
            painted.add((position[0], position[1]))
        else:
            n = int(command.split()[0])
            for i in range(n):
                if (ind + 1) < len(actions):
                    f(ind + 1, cnt0 + 4)
        ind += 1

fin = open("input.txt", 'r')


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

f(0, 0)
print(len(painted))
fin.close()
