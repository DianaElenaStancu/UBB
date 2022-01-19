def compute_sum(b, M):
    """
    Calculeaza suma totala aferenta listei solutiei b in functie de M
    e.g. M=98, b=[50, 10, 5] -> amount_so_far = 1x50+4*10+1x5 = 95
    :param b: lista data
    :type b: list of int
    :param M: suma totala care trebuie platita
    :type M: int
    :return: suma totala aferenta bancnotelor din b calculate in functie de M
    :rtype: int
    """
    amount_so_far = 0
    for val_bancnota in b:
        # calculam numarul de bancnote care intra in suma curenta
        # (M-amount_so_far) si nu doar M pentru ca de ex. pentru
        # e.g. M=98, b=[50,10, 5] -> I)
        # amount_so_far = 0
        # bancnota=50 -> nr_bancnote= (98-0)//50 = 1 -> amount_so_far = 0+50= 50
        # bancnota=10 -> nr_bancnote= (98-50)//10 = 4 -> amount_so_far = 50+40= 90
        # bancnota=5 -> nr_bancnote= (98-90)//5 = 1 -> amount_so_far = 90+5= 95

        nr_bancnote = (M - amount_so_far) // val_bancnota
        if nr_bancnote == 0:
            nr_bancnote += 1
        amount_so_far += nr_bancnote * val_bancnota
    return amount_so_far


def solution(b, M):
    sum_b = compute_sum(b, M)
    return sum_b == M


def acceptabil(b, M):
    sum_crt_b = compute_sum(b, M)
    return sum_crt_b <= M


def selectMostPromising(c):
    return max(c)


def print_solution(b, M):
    amount = 0
    for val_bancnota in b:
        nr_bancnote = (M - amount) // val_bancnota
        amount += nr_bancnote * val_bancnota
        print('{}x{}'.format(val_bancnota, nr_bancnote), end='')
        if amount != M:
            print('+', end='')
        else:
            print('={}'.format(M))


def greedy(c, M):
    b = []
    while not solution(b, M) and c != []:
        candidate = selectMostPromising(c)
        c.remove(candidate)
        if acceptabil(b + [candidate], M):
            b.append(candidate)

    if solution(b, M):
        print_solution(b, M)
        return b
    return None


def test_greedy_bancnote2():
    c1 = [5, 10, 25]
    M1 = 95

    assert (greedy(c1, M1) == [25, 10])

    c2 = [5, 10, 25]
    M2 = 93
    # nu exista solutie cu bancnotele date
    assert (greedy(c2, M2) == None)

    c3 = [1, 2, 5, 25]
    M3 = 93

    assert (greedy(c3, M3) == [25, 5, 2, 1])

    c4 = [1, 2, 10, 25]
    M4 = 51

    assert (greedy(c4, M4) == [25, 1])

    c5 = [5, 10, 25]
    M5 = 3
    # nu exista solutie cu bancnotele date
    assert (greedy(c5, M5) == None)
