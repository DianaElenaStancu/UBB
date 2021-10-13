"""Fie n un număr natural dat. Calculați produsul p al tuturor factorilor
 proprii ai lui n."""
import math

n = int(input())
p = 1
    
for i in range(2, math.floor(math.sqrt(n)) + 1):
    if n%i == 0:
        print(i, int(n/i))
        p = p * i * int(n/i)

    
print(p)
