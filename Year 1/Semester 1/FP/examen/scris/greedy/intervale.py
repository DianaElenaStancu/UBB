"""
You are given n activities with their start and finish times. Select the maximum number of activities
 that can be performed by a single person, assuming that a person can only work on a single activity at a time.
"""
"""
greedy:

1. multime candidat: multimea de unde se aleg elementele solutiei

2. functia de selectie: functia care alege cel mai bun element
pentru a fi adaugat la solutie
 
3. functia acceptabil: functia folosita pentru a determina daca un
candidat curent poate contribui la solutie pentru problema

4. functia obiectiv: functie care calculeaza o valoare 
pentru solutie/solutii partiale

5. functia solutie: functie care verifica daca s-a ajuns la o solutie
pentru problema 

"""
def selectMostPromissing(a):
    """
    selectez activitatea care se termina cel mai repede
    """
    endTime = a[0][1]
    intervalMin = a[0]
    for interval in a:
        if interval[1] < endTime:
            endTime = interval[1]
            intervalMin = interval
    return intervalMin

def acceptable(a):
    """
    vad daca activitatea nou adaugata nu se suprapune cu cea precedenta
    """
    if len(a) == 1:
        return True
    return a[-2][1] <= a[-1][0]

def greedy(a):
    sol = []
    while a != []:
        candidate = selectMostPromissing(a)
        a.remove(candidate)
        if acceptable(sol + [candidate]):
            sol = sol + [candidate]
    return sol


activitati = [(1, 2), (3, 4), (0, 6), (5, 7), (8, 9), (5, 9)]
print(greedy(activitati))