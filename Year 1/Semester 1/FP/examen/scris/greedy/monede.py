"""
Se da o sumă M și tipuri (ex: 1, 5, 25) de monede (avem un numar nelimitat de monede
din fiecare tip de monedă). Să se găsească o modalitate de a plăti suma M de bani folosind cât
mai puține monezi.

"""
"""
set candidat: lista de monede
solutie candidat: o lista de monede
x = (x0, x1, .., xk), xi apartine listei de monede

functie de selectie:
    solutie candidat: x = (x0, x1, .., xk)
    alege moneda cea mai amre care e mai mic decat ce mai e de platit
    
acceptabil:
    solutie candidat: x = (x0, x1, .., xk)
    suma monedelor din solutia candidat nu depaseste suma ceruta

solutie:
    solutie candidat: x = (x0, x1, .., xk)
    suma monedelor din solutia candidat este egala cu suma ceruta

"""
def selectMostPromising(c, b, M):
    most_promising = 0
    for candidate in c:
        if candidate +sum(b) <= M and candidate > most_promising:
            most_promising = candidate
    return most_promising

def acceptable(lst, M):
    return sum(lst) <= M

def solution(lst, M):
    return sum(lst) == M

def greedy(monede, M):
    b = []

    while not solution(b, M):
        candidate = selectMostPromising(monede, b, M)
        if candidate == 0:
            break
        if acceptable(b + [candidate], M):
            b.append(candidate)
    if solution(b, M):
        return b
    return None


monede = [1,5,25]
M = 30
print(greedy(monede, M))
