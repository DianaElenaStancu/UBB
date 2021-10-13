#calculati cel mai mare divizor comun a doua numere 
from typing import Union
def cmmdc(a, b)->Union[int,str]:
    if a < 0 or b < 0:
        return "nu exista"
    else:
        while b != 0:
            r = a % b
            a = b
            b = r
        return a

n1 = int(input())
n2 = int(input())
print(cmmdc(n1, n2))
