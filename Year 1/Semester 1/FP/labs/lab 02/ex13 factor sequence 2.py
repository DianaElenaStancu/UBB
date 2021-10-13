""" Determinați al n-lea element al șirului
 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...
 obținut din șirul numerelor naturale prin înlocuirea numerelor compuse prin
 divizorii lor primi, fiecare divizor prim d repetându-se de d ori, fără
 a retine termenii șirului!"""

import math
def estePrim(x):
    if x < 2:
        return 0
    if x == 2:
        return 1
    if x%2 == 0:
        return 0
    for div in range(3, math.ceil(math.sqrt(x)) + 1, 2):
        if x%div == 0:
            return 0
    return 1

n = int(input())
an = 1 # sequence of natural numbers: an

if n == 1:
    print(1)
else:
    n = n - 1
    factor = 1
    while n > 0:
        if estePrim(an)==1:
            n = n - 1
            factor = an
            #print(factor)
        else:
            copy = an
            div = 2
            while copy > 1 and n > 0:
                if copy%div == 0:
                    while copy%div == 0:
                        copy = copy/div
                    factor = div
                    #print(factor, "*", factor)
                    n = n - div
                div = div + 1
        an = an + 1
        
    print(factor)
