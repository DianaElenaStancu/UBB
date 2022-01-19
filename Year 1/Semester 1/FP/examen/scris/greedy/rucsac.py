"""

multimea candidat

functie selectie: se selecteaza obiectul cu valoarea cea mai mare
si greutatea cea mai mic, greutate mai mica decat capacitatea ghiozdanului

functie acceptabil: suma greutatile sa fie mai mica/egala decat capacitate


functie solutie: suma greutatilor sa fie mai mica sau egala decat capacitatea
si sa nu mai existe alte obiecte care se pot adauga

"""


def findBestObject(value, weight, w):
    max_val = 0
    pos = -1
    for i in range(len(value)):
        if weight[i] <= w and max_val < value[i]:
            pos = i
            max_val = value[i]
    return pos



def greedy(value, weight, w):
    v = 0
    while len(value) > 0:
        pos = findBestObject(value, weight, w)
        if pos == -1:
            break
        w -= weight[pos]
        v += value[pos]
        value.pop(pos)
        weight.pop(pos)
    return v


value= [10, 15, 40]
weight = [1, 2, 3]
w = 6
print(greedy(value, weight, w))