"""Determinati al n-lea element al șirului
 1,2,3,2,5,2,3,7,2,3,2,5,...
 obținut din șirul numerelor naturale prin înlocuirea numerelor compuse prin
 divizorii lor primi, fără a retine termenii șirului.

 1 -> 1
 2 -> 2
 3 -> 3
 4 -> 2
 5 -> 5
 6 -> 2 3
 7 -> 7
 8 -> 2
 9 -> 3
 10 -> 2 5

 """

n = int(input())
an = 1 #sirul an format din numere naturale
f = 1 #factorii fiecarui numar din sirul an
n = n - 1

while n > 0:
    copy = a
    div = 2
    while copy > 1 and n > 0:
        if copy%div == 0:
            while copy%div == 0 and n > 0:
                copy = copy/div
            f = div
            n = n - 1
            #print(f)
        div = div + 1
    a = a + 1

print(f)
