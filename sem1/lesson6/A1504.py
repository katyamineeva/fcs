def checkNotation(notation, radix):
	if notation[0] == '-':
		return False
		
	allowedSymb = []
	left = ord('0')
	right = min(ord('9') + 1, ord('0') + radix)
	for i in range(left, right):
		allowedSymb.append(chr(i))
	
	left = ord('A')
	right = min(ord('Z') + 1, ord('A') + radix - 10)
	for i in range(left, right):
		allowedSymb.append(chr(i))
	allowedSymb = set(allowedSymb)
	
	for i in notation:
		if i not in allowedSymb:
			return False
	return True


radix = int(input())
notation = input()

if checkNotation(notation, radix):
	print("YES")
else:
	print("NO")
