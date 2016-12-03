def generate(key, problems=4, variants=4):
       r = 0
       for c in key:
           r += ord(c)
       result = []
       for j in range(problems):
           result.append(chr(ord('A') + j) + str(r % variants + 1))
           r //= variants
       return result

fout = open("problems.txt", "w")

s = generate("wScCOutRNB")
print(s)
tmp = ' '.join(s)
fout.write(tmp)
print(tmp)
