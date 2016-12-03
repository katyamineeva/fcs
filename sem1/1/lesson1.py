
"""

print "what's your name?"
name = raw_input()
s = "hello, " + name

cnt = 0
for symb in s:
	if symb == 'e':
		cnt += 1
		
print cnt
k = s.count('e')
if k == cnt:
	print "YES"
"""
"""
# age = int(input("what's your age?"))

print "how old are you?"
age = input()
print "your birth's date: " + str(2015 - age)


s = "Andrey, Sergey, Andrey, Dmitry"
s = s.split(", ")
s.sort()
s = ", ".join(s)
print s

# join - split 

a = input()
b = input()

c = (a ** 2 + b ** 2) ** 0.5
print c 



num = int(input())
p = int(input())

actions = []
res = num

while p != 1:
	if p % 2 == 0:
		actions.append(2)
		p /= 2
	else:
		actions.append(1)
		p -= 1

while len(actions) > 0:
	if actions.pop() == 1:
		res *= num
	else:
		res *= res
		
		
print(res)

"""

