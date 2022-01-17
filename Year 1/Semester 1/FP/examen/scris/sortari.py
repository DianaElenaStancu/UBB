"""
sortari:
    prin selectie
    prin selectie directa
    prin insertie
    metoda bulelor
    quicksort
    mergesort

se utilizeaza spatiu de memorie ---> out-of-place
NU se utilizeaza spatiu de memorie ---> in-place
"""


def selectionSort(l):
    """
    sortare elementele din lista l
    :param l: lista de elemente
    :return: lista ordonata
    """
    for i in range(0, len(l) - 1):
        ind = i
        #cauta cel mai mic element din restul listei
        for j in range(i + 1, len(l)):
            if (l[j] < l[ind]):
                ind = j
        if (i < ind):
            #interschimbare
            aux = l[i]
            l[i] = l[ind]
            l[ind] = aux

"""
ex:  0  1  2  3  4  5  6
l = [5, 3, 2, 7, 4, 0, 1]
  = [0, 3, 2, 7, 4, 5, 1]
  = [0, 1, 2, 7, 4, 5, 3]
  = [0, 1, 2, 7, 4, 5, 3]
  = [0, 1, 2, 3, 4, 5, 7]
  
  
i: 2
ind: 6
j: 6

"""


def directSelectionSort(l):
    """
    sortare elementele din lista l
    :param l: lista de elemente
    :return: lista ordonata
    """
    for i in range(0, len(l) - 1):
        #selectez elementul cel mai mic
        for j in range(i+1, len(l)):
            if l[j] < l[i]:
                l[i], l[j] = l[j], l[i]

def insertSort(l):
    """
    sortare elementele din lista l
    :param l: lista de elemente
    :return: lista ordonata
    """
    for i in range(1, len(l)):
        ind = i - 1
        a = l[i]
        #inserez a la pozitia corecta
        while ind >= 0 and a < l[ind]:
            l[ind + 1] = l[ind]
            ind = ind - 1
        l[ind + 1] = a

"""
ex:  0  1  2  3  4  5  6
l = [5, 3, 2, 7, 4, 0, 1]
l = [3, 5, 2, 7, 4, 0, 1]
l = [2, 3, 5, 7, 4, 0, 1]
l = [2, 3, 4, 5, 7, 0, 1]
l = [0, 2, 3, 4, 5, 7, 1]
l = [0, 1, 2, 3, 4, 5, 7]

i: 1->2->3->4->5->6
ind: 0->-1-->1->0->-1-->2-->3->2->1-->4->3->2->1->0->-1-->5->4->..->1->0
a: 3->2->7->4->0->1

"""

def bubbleSort(l):
    sorted = False
    while not sorted:
        sorted = True #presupunem ca lista noastra este sortata
        for i in range(len(l) - 1):
            if l[i + 1] < l[i]:
                sorted = False #lista mea nu este sortata (asa cum am presupus)
                l[i], l[i + 1] = l[i + 1], l[i]

def bubbleSort2(l):
    for j in range(1, len(l)):
        for i in range(len(l) - j):
            if l[i + 1] < l[i]:
                l[i], l[i + 1] = l[i + 1], l[i]
"""
ex:  0  1  2  3  4  5  6 -- len(l) = 7
l = [5, 3, 2, 7, 4, 0, 1]
l = [3, 2, 5, 4, 0, 1, 7] ---> la fiecare iteratie se duce in final elementul cel mai mare 
l = [2, 3, 4, 0, 1, 5, 7] 

j (1->6):1, 2
i (0->6); (0->5)

"""

#QuickSort
def partition(l, left, right):
    """
    Despartim valorile:
        mai mic - pivot - mai mare
    :return: pozitia pivot
    :pos: numere mai mici decat pivot - pivot - numere mai mari decat pivot
    """
    #scopul meu final este ca pivotul ales sa il mut in pozitia
    #corecta, in stanga sa am elemente mai mici, in dreapta elemente
    #mai mari
    pivot = l[left]
    i = left
    j = right
    while i != j:
        #incep din dreapta si ma opresc in momentul in care nu mai am
        #numere mai mari decat pivotul
        while l[j] >= pivot and i < j:
            j = j - 1
        #mut pivotul in locul unde are toate elementele
        #din dreapta mai mari
        l[i] = l[j]
        #incep din stanga si ma opresc in momentul in care
        #nu mai am numere mai mici decat pivotul
        while l[i] <= pivot and i < j:
            i = i + 1
        #mut pivotul in locul unde are toate elementele
        #din stanga mai mici
        l[j] = l[i]
    #noul pivot
    l[i] = pivot
    #returnez pozitia la care se afla pivotul
    return i

def quickSortRec(l, left, right):
    #partitionam lista
    pos = partition(l, left, right)
    #ordonam partea stanga
    if left < pos - 1:
        quickSortRec(l, left, pos - 1)
    #ordonam partea dreapta
    if pos + 1 < right:
        quickSortRec(l, pos + 1, right)

"""
ex:  0  1  2  3  4  5  6 -- len(l) = 7
l = [5, 3, 2, 7, 4, 0, 1]
l = [1, 3, 2, 0, 4, 5, 7]
l = [0, 1, 2, 3, 4, 5, 7]

quickSortRec(l, 0, 6)

pos = partition(l, 0, 6) = 5
    left = 0
    right = 6
    pivot = 5
    i = 0-->3-->5
    j = 6-->5
    return 5

quickSortRec(l, 0, 4)


pos = partition(l, 0, 4) = 1
    ex:  0  1  2  3  4  5  6
    l = [0, 1, 2, 3, 4,| 5, 7]
    
    left = 0
    right = 4
    pivot = 1
    i = 0-->1
    j = 4-->3-->2-->1
    return 1

quickSortRec(l, 2, 4) = 4
"""

def quickSort(list):
    """
    list comprehensions
    """
    if len(list) <= 1:
        return list
    pivot = list.pop()
    lesser = quickSort([x for x in list if x < pivot])
    greater = quickSort([x for x in list if x >= pivot])
    return lesser + [pivot] + greater
"""
ex:  0  1  2  3  4  5  6 -- len(l) = 7
l = [5, 3, 2, 7, 4, 0, 1]

pivot = 1
lesser = q([0]) = [0]
greater = q([5, 3, 2, 7, 4])

"""

def merge(l, start, end, m):
    left = l[start:(m+1)]
    right = l[(m+1):(end+1)]
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
    if end-start < 1:
        return
    m = (end+start)//2
    mergeSort(l, start, m)
    mergeSort(l, m+1, end)
    merge(l, start, end, m)

l = [5,4,3,2, 0, 54384, -384034, 4,3 ,2 -1, 0, 0, 2]
mergeSort(l, 0, 13)
print(l)