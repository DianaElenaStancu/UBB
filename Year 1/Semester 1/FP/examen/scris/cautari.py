"""
tipuri cautari:
    1. secventiala
    2. succesiva
    3. binara
"""
"""
precizari suplimentare:

range(a, b): a, a+1, a+2, ...., b-2, b-1
ex: range(0, 3): 0, 1, 2


"""

"""
specificatii pentru cautare

date: a, n (ki, i = 0, n - 1)
    preconditii: n natural, n >= 0
rezultate: p
    post_conditii: (0<=p<=n-1 si a = kp) sau 
    p = -1 daca cheia nu exista 
"""


def cautaSecv(el, l):
    """
    cauta un element dintr-o lista
    :param el: elementul cautat
    :param l:  lista de elemente
    :return: pozitia la care se afla elementul
    sau -1 in cazul in care nu exista acest element
    in lista l
    """
    poz = -1
    for i in range(0, len(l)):
        if el == l[i]:
            poz = i
    return poz


def cautaSucc(el, l):
    """
    cauta un element dintr-o lista
    :param el: elementul cautat
    :param l: lista de elemente
    :return: pozitia primei aparitii
    sau -1 daca elementul nu exista in
    lista l
    """
    i = 0
    while i < len(l) and el != l[i]:
        i = i + 1
    if i < len(l):
        return i
    return -1

"""
specificatii pentru cautare - chei ordonate

date: a, n (ki, i = 0, n-1)
    preconditii: n natural n>= 0, si k0 <k1 <...<kn-1
rezultate: p
    post_conditii: (p = 0 si a <= k0) or (p = n si a > kn-1)
    (0<p<=n-1) si (kp-1<a<=kp)

"""

def cautaSecvOrd(el, l):
    """
    cauta un element din lista
    :param el:  elementul
    :param l:   lista de elemente ordonate
    :return: pozitia primei aparitii sau pozitia
    unde poate fi inserat elementul
    """
    if len(l) == 0:
        return 0
    poz = -1
    for i in range(0, len(l)):
        if el <= l[i]:
            poz = i
    if poz == -1:
        return len(l)
    return poz

def cautaSuccOrd(el, l):
    """
    cauta un element din lista
    :param el:  elementul
    :param l:   lista de elemente ordonate
    :return: pozitia primei aparitii sau pozitia
    unde poate fi inserat elementul
    """
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



"""
    recurenta cautare binara 
    T(n) = O(1), n = 1
           T(n/2) + O(1), caz contrar
"""
def cautaBinarS(el, l, left, right):
    """
    cauta un element din lista
    :param el: elementul care trebuie cautat
    :param l:  lista ordonata de elemente
    :param left,right: sublista in care cautam elementul el
    :return:  pozitia primei aparitii
    sau a pozitie unde trebuie inserat elementul
    """
    if left >= right-1:
        return right
    m = (left+right)//2
    if el <= l[m]:
        return cautaBinarS(el, l, left, m)
    else:
        return cautaBinarS(el, l, m, right)


def cautaBinarRec(el, l):
    """
    cauta un element din lista
    :param el: elementul care trebuie cautat
    :param l:  lista ordonata de elemente
    :return:  pozitia primei aparitii
    sau a pozitie unde trebuie inserat elementul
    """
    if len(l) == 0:
        return 0
    if el < l[0]:
        return 0
    if el > l[len(l) - 1]:
        return len(l)
    return cautaBinarS(el, l, 0, len(l))

def cautBinarIterativ(el, l):
    """
    cauta un element din lista
    :param el: elementul care trebuie cautat
    :param l:  lista ordonata de elemente
    :return:  pozitia primei aparitii
    sau a pozitie unde trebuie inserat elementul
    """
    if len(l) == 0:
        return 0
    if el <= l[0]:
        return 0
    if el >= l[len(l) - 1]:
        return len(l)
    right = len(l)
    left = 0
    while right - left > 1:
        m = (left+right)//2
        if el <= l[m]:
            right = m
        else:
            left = m
    return right

"""
     0 1 2 3 4 
l = [1,2,3,4,5]
el = 4
left = 0->2
right = 5->3
m = 3


"""

class Person:
    def __init__(self, id, name):
        self.id = id
        self.name = name
    def __eq__(self, other):
        return self.id == other.id
def testIndex():
    l = []
    for i in range (0, 200):
        p = Person(i, "ad")
        l.append(p)
    findPerson = Person(32, "abc")
    print(l.index(findPerson))
    print(findPerson in l)


testIndex()

class MyClass2:
    def __init__(self):
        self.l = []
    def add(self,obj):
        self.l.append(obj)
    def __iter__(self):
        """
        Return an iterator object
        """
        self.iterPoz = 0
        return self
    def __next__(self):
        if(self.iterPoz >= len(self.l)):
            raise StopIteration()
        rez = self.l[self.iterPoz]
        self.iterPoz = self.iterPoz + 1
        return rez

def testIn():
    container = MyClass2()
    for i in range(0,200):
        container.add(Person(i, "ad"))
    findObj = Person(20, "djsoaj")
    print(findObj in container)


testIn()

"""l = [1,2,3,4,5]
print(cautaBinarRec(4, l))"""