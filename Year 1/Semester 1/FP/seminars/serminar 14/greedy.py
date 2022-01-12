"""
metoda greedy

backtracking: generate & test
greedy: alege la fiecare pas cea mai buna optiune

a) mt candidat
b) functie de selectie
c) functie acceptabil
d)*functie obiectiv
e) functia de solutie



1) se dau o serie de bancnote si o suma M.
sa se gaseasca modalitatea de a plati suma M cu cele mai putine bancnote
"""


def greedy(M, c):
    b = []
    while not solution(b, M) and c != []:
        candidate = selectMostrPromising(c)
        c.remove(candidate)
        if acceptabil(b +[candidate]):
            b.append(candidate)
        if solution(b, M):
            return b
        return None

def acceptabil(n, M):
    return compute_sum(b, M) <= M

def selectMostrPromising(c):
    return max(c)

def solution(b, M):
    return compute_sum(b, M)== M

def compute_sum(b, M):
    """
    b - solutia pe care o construim
    M - suma data
    :param b:
    :param M:
    :return:
    """
    sum_par = 0
    for banc in b:
        nr_banc = (M-sum_par)
        suma_par = nr_banc*banc
    return sum_par

