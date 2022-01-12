"""
se da o lista de nr. sa se verifice daca exista nr impare in lista
"""
def exista_impare(lista):
    if len(lista) == 1:
        if lista[0]%2 == 1:
            return 1
        return 0
    m = len(lista)//2
    return max(exista_impare(lista[m:]), exista_impare(lista[:m]))
#return exista_impare(lista[m:]) or exista_impare(lista[:m])

