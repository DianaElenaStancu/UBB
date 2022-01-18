def suma(x):
    """
    Calculeaza suma elementelor unei liste date
    :param x: lista cu elemente numere naturale
    :type x: list
    :return: suma elementelor listei
    :rtype: int
    """
    return sum(x)


def consistent(x, s):
    if x[0] == 0:
        return False
    if suma(x) > s:
        return False
    for i in range(len(x) - 1):
        if abs(x[i] - x[i + 1]) % 2 == 0:
            return False
    return True


def solutie(x, s, n):
    if len(x) == n and suma(x) == s:
        return True
    return False


def backtrack_rec(x, s, n):
    x.append(0)
    for cifra in range(10):
        x[-1] = cifra
        if consistent(x, s):
            if solutie(x, s, n):
                print('Solutie:', ''.join([str(cifra) for cifra in x]))
            else:
                backtrack_rec(x[:], s, n)
    x.pop()


backtrack_rec([], 8, 4)
