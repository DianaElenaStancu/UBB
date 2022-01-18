def consistent(x):
    if len(set(x)) != len(x):
        return False
    else:
        for i in range(1, len(x), 2):
            if x[i] != i+1:
                return False

        return True


def back_rec(x, n):
    x.append(1)
    for i in range(1, n + 1):
        x[-1] = i
        if consistent(x):
            if len(x) == n:
                print('Solutie:', x)
            else:
                back_rec(x[:], n)
    x.pop()


back_rec([], 5)
