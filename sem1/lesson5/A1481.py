import sys

def lenght(x1, y1, x2, y2):
	return ((x1 - x2) ** 2  + (y1 - y2) ** 2) ** 0.5

x1 = float(input())
y1 = float(input())
x2 = float(input())
y2 = float(input())
# or 
print(lenght(x1, y1, x2, y2))
