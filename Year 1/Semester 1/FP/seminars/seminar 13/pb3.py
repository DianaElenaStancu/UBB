"""
se da o lista de nr. sa se calculeze suma elementelor pare
"""

def suma_pare(lst):
    if len(lst) == 1:
        if lst[0]%2 == 0:
            return lst[0]
        return 0
    m = len(lst)//2
    return suma_pare(lst[m:]) + suma_pare(lst[:m])