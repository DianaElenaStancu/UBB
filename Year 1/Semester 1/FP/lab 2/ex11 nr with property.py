"""Numerele n1 si n2 au proprietatea P daca scrierile lor in baza 10 conțin
 aceleași cifre (ex. 2113 si 323121). Determinați daca doua numere naturale
 au proprietatea P"""

n1 = input()
n2 = input()

stdr = 1
drst = 1

for digit in n1:
    if n2.find(digit) == -1:
        stdr = 0

for digit in n2:
    if n1.find(digit) == -1:
        drst = 0

if stdr == 1 and drst == 1:
    print("au proprietatea P")
else:
    print("nu au proprietatea P")

