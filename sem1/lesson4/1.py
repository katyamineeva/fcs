def vectorPlus(v1, v2):
	assert(len(v1) == len(v2))
	return [v1[i] + v2[i] for i in range(len(v1))]

def matrixPlus(m1, m2):
	assert(len(m1) == len(m2))
	return [vectorPlus(m1[i], m2[i]) for i in range(len(m1))]
	
def scalarMult(v1, v2):
	assert(len(v1) == len(2))	

def mvMult(m, v):
	assert(len(m) == len(v))
	return [scalarMult(m[i], v) for i in range(len(m))]
	

def matrixMult(m1, m2):
	m2 = list(zip(*m2))
	resM = [mvMult(m1, m2[i]) for i in range(len(m2))]
	return list(zip(*l))


## base if a list of dicts. Examples [..., {"name": "Anna", "year": "1997"}, ...]

st = set()
for dic in lst:
	tmp = [(key, dic[key]) for key in dic]
	st.add(tuple(tmp))
