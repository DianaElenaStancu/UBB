from functools import reduce


def get_divizori(n):
    divizori = []
    for i in range(2, n // 2 + 1):
        if n % i == 0:
            divizori.append(i)
    return divizori


def produs(x):
    """
    Calculeaza produsul elementelor unei liste date
    :param x: lista de numere naturale
    :type x: list
    :return: produsul elementelor
    :rtype: int
    """
    return reduce((lambda x, y: x * y), x)


def consistent(x, n):
    for i in range(len(x) - 1):
        if x[i] > x[i + 1]:
            return False

    crt_prod = produs(x)
    if crt_prod > n:
        return False
    return True


def divizori_rec(x, n, divizori):
    d = divizori[0]
    x.append(d)
    for d in divizori:
        x[-1] = d
        if consistent(x, n):
            if produs(x) == n:
                print('Solutie:', x)
            else:
                divizori_rec(x[:], n, divizori)
    x.pop()


divizori_rec([], 30, get_divizori(30))
