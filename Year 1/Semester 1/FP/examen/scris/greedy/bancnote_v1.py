"""
1.Se dă o sumă M și tipuri de bancnote.
Să se găsească o modalitate de a plăti
suma M de bani folosind cât mai puține bancnote.
"""


def solution(b, M):
    return sum(b) == M


def selectMostPromising(c, b, M):
    most_promising = 0
    for candidate in c:
        if candidate + sum(b) <= M and candidate > most_promising:
            most_promising = candidate
    return most_promising


def acceptable(lst, M):
    return sum(lst) <= M


def solution(lst, M):
    return sum(lst) == M


def greedy(c, M):
    b = []

    while not solution(b, M):
        candidate = selectMostPromising(c, b, M)
        # my_candidates.remove(crt_cmponent)
        if candidate == 0:
            break
        if acceptable(b + [candidate], M):
            b.append(candidate)
    if solution(b, M):
        return b
    return None


def test_greedy_bancnote1():
    c1 = [5, 10, 25]
    M1 = 95

    assert (greedy(c1, M1) == [25, 25, 25, 10, 10])

    c2 = [5, 10, 25]
    M2 = 93
    # nu exista solutie cu bancnotele date
    assert (greedy(c2, M2) == None)

    c3 = [1, 2, 5, 25]
    M3 = 93

    assert (greedy(c3, M3) == [25, 25, 25, 5, 5, 5, 2, 1])

    c4 = [1, 2, 10, 25]
    M4 = 51

    assert (greedy(c4, M4) == [25, 25, 1])

    c5 = [5, 10, 25]
    M5 = 3
    # nu exista solutie cu bancnotele date
    assert (greedy(c5, M5) == None)
