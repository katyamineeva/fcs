
def merge(lst1, lst2):
    i1 = 0
    i2 = 0
    lstSorted = []
    while i1 < len(lst1) and i2 < len(lst2):
        if lst1[i1] <= lst2[i2]:
            lstSorted.append(lst1[i1])
            i1 += 1
        else:
            lstSorted.append(lst2[i2])
            i2 += 1
                        
    for i in range(i1, len(lst1)): lstSorted.append(lst1[i])
                
    for i in range(i2, len(lst2)): lstSorted.append(lst2[i])

    return lstSorted
        
        
def mergeSort(lst):
	n = len(lst)
	if len(lst) <= 1:
		return lst
	return merge(mergeSort(lst[:n // 2]), mergeSort(lst[n // 2:]))


print(mergeSort([57, 1, 3, 4, -2, 17]))
