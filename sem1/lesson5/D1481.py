def power(a, n):
	if n == 0:
		return 1
	if n == 1:
		return a
	return power(a, n // 2) * power(a, n // 2) * power(a, n % 2)

a = float(input())
n = int(input())

if n > 0:
	print(str(power(a, n)))
else:
	print(str(1 / power(a, -n)))
