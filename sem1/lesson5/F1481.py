def rev():
	tmp = int(input())
	if tmp != 0:
		rev()
	print(str(tmp))

rev()

