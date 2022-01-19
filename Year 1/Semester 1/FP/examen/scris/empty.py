"""
CAUTARE:
    SECVENTIALA
    SUCCESIVA
    BINARA

SORTARI
    PRIN SELECTIE
    PRIN SELECTIE DIRECTA
    PRIN INSERTIE
    METODA BULELOR
    QUICKSORT
    MERGESORT
"""
#chei neordonate
#eu vreau sa caut elementul el in lista si sa returnez pozitia la care se afla
def searchSeq(el, l):
    poz = -1
    for i in range(len(l)):
        if l[i] == el:
            poz = i
    return poz

def searchSucc(el, l):
    i = 0
    while i < len(l) and el != l[i]:
        i += 1
    if i < len(l):
        return i
    return -1

#chei ordonate
#eu vreau sa caut pozitia unde pot insera elementul dat
def searchSeqOrd(el, l):
    if len(l) == 0:
        return 0
    poz = -1
    for i in range(len(l)):
        if el <= l[i]:
            poz = i
    if poz == -1:
        return len(l)
    return poz

def searchSuccOrd(el, l):
    if len(l) == 0:
        return 0
    if el <= l[0]:
        return 0
    if el >= l[len(l) - 1]:
        return len(l)
    i = 0
    while i < len(l) and el > l[i]:
        i = i + 1
    return i


def binaryS(el, l, left, right):
    if left == right:
        return right
    m = (left + right)//2
    if el <= l[m]:
        return binaryS(el, l, left, m)
    else:
        return binaryS(el, l, m+1, right)


def searcBinaryRec(el, l):
    if len(l) == 0:
        return 0
    if el < l[0]:
        return 0
    if el > l[len(l) - 1]:
        return len(l)
    return binaryS(el, l, 0, len(l) - 1)

def searchBinaryNonRec(el, l):
    if len(l) == 0:
        return 0
    if el < l[0]:
        return 0
    if el > l[len(l) - 1]:
        return len(l)
    left = 0
    right = len(l)-1
    while left < right:
        m = (left + right) // 2
        if el <= l[m]:
            right = m
        else:
            left = m + 1
    return right

def selectionSort(l):
    for i in range(len(l) - 1):
        ind = i
        for j in range(i + 1, len(l)):
            if l[j] > l[ind]:
                ind = j
        if ind > i:
            aux = l[i]
            l[i] = l[ind]
            l[ind] = aux

def directSelectionSort(l):
    for i in range(len(l) - 1):
        for j in range(i + 1, len(l)):
            if l[j] > l[i]:
                l[j], l[i] = l[i], l[j]


def insertionSort(l):
    for i in range(1, len(l)):
        ind = i - 1
        a = l[i]
        while ind >= 0 and a < l[ind]:
            l[ind + 1] = l[ind]
            ind = ind - 1
        l[ind + 1] = a


#in place: nu utilizeaza memorie suplimentara
def partition(l, left, right):
    pivot = l[left]
    i = left
    j = right
    while i != j:
        while i < j and l[j] >= pivot:
            j = j - 1
        l[i] = l[j]
        while i < j and l[i] <= pivot:
            i = i + 1
        l[j] = l[i]
    l[i] = pivot
    return i


def quickSort1(l, left, right):
    pos = partition(l, left, right)
    if pos + 1 < right:
        quickSort1(l, pos + 1, right)
    if pos - 1 > left:
        quickSort1(l, left, pos - 1)

#out place: lists comprehensions
def quickSort2(l):
    if len(l) <= 1:
        return l
    pivot = l.pop()
    lesser = quickSort2([x for x in l if x < pivot])
    greater = quickSort2([x for x in l if x >= pivot])
    return lesser + [pivot] + greater


def merge(l, start, end, mid):
    left = l[start:(mid + 1)]
    right = l[(mid+1):(end + 1)]
    i = 0
    j = 0
    k = start
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            l[k] = left[i]
            i += 1
        else:
            l[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        l[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        l[k] = right[j]
        j += 1
        k += 1


def mergeSort(l, start, end):
    if start >= end:
        return
    mid = (start + end)//2
    mergeSort(l, start, mid)
    mergeSort(l, mid + 1, end)
    merge(l, start, end, mid)




l = [4,5,7,0,2,4,7,2]
mergeSort(l, 0, len(l)-1)
print(l)