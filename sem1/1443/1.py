"""

n = int(input())
b = range(1, n + 1, 2) #not list !!!
a = list(range(1, n + 1, 2)) #list !!!
print(b)
print(a)



lst = [1, 3, 5, 7, 9]
#lst.pop(0)
#lst.pop()

lst = lst[1:4]
print(lst)

st = set(lst)

st1 = set(1, 9)

st = st - st1 ## it's possible!!


lst_w = [] ## list if words in Eugeniy.O
d = {}
for  i in lst_w:
	if i in d:
		d[i] += 1
	else:
		d[i] = 1
		
		
or


for i in lst:
	d[i] = d.get(i, 0) + 1
	or
	d.setdefault(i, 0) += 1

lst[::-3] # from last elem to first . step = 3


d1 = {(1, "57"), ("pfpfpf", 1)}
"""

lst1 = [
{
name: Anna
year: 1997
}
]

lst2 = [
{
name: Jack
year: 1991
}
]

d = {}

for man in lst1:
	tmp = (man["name"], man["year"])
	d[tmp] = man
		 

