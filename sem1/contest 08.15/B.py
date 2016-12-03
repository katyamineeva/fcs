finput = open("input.txt", "r")
foutput = open("output.txt", "w")


n = int(finput.readline())
a = [int(x) for x in finput.readline().split()]
m = int(finput.readline())

ans = []

for i in range(m):
    x = int(finput.readline())
    k = 0
    ans = []
    
    if (x != 0):
        for i in a:
            if (i % x == 0):
                k += 1
                ans.append(i)
                
        foutput.write(str(k) + "\n")
        if (k == 0):
            foutput.write("\n")
        else:
            for i in ans:
                foutput.write(str(i) + " ")
            foutput.write("\n")
    else:
        foutput.write("0\n\n")
        
finput.close()
foutput.close()