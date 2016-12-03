maxValue = 575757
x = int(input())
cosX = 1
factorials = [1]
for i in range(2, 2 * maxValue + 1):
	factorials.append(factorials[-1] * i)

for n in range(maxValue):
	cosX += ((-1) ** n) * (x ** (2 * n)) / factorials[2 * n]
