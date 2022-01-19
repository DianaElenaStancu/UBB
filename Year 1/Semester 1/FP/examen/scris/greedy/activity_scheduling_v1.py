"""
You are given n activities with their start and finish times. Select the maximum number of activities
 that can be performed by a single person, assuming that a person can only work on a single activity at a time.
"""
import math
import random


def select_most_promising(c):
    """
    Selecteaza activitatea care se termina cel mai repede din lista de candidati
    """
    min_index = math.inf
    min_finish_time = math.inf

    for index, activity in enumerate(c):
        if activity[1] < min_finish_time:
            min_finish_time = activity[1]
            min_index = index
    return c[min_index]


def acceptable(b):
    if len(b) == 1:
        return True
    if b[-1][0] >= b[-2][1]:
        return True
    return False


def solution(b):
    pass


def greedy(c):
    b = []
    while c != []:
        candidate = select_most_promising(c)
        c.remove(candidate)

        if acceptable(b + [candidate]):
            b.append(candidate)
    return b


def test_activity_scheduling1():
    c1 = [(10, 20), (12, 25), (20, 30)]
    random.shuffle(c1)
    assert (greedy(c1) == [(10, 20), (20, 30)])

    c2 = [(1, 2), (3, 4), (0, 6), (5, 7), (8, 9), (5, 9)]
    random.shuffle(c2)
    assert (greedy(c2) == [(1, 2), (3, 4), (5, 7), (8, 9)])

    c3 = [(1, 2), (1, 4), (1, 3)]

    # raspunsul e 1 activitate - oricare ar fi raspuns corect
    # implementarea curenta returneaza [(1,2)]
    assert (greedy(c3) == [(1, 2)])
