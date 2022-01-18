def f(n):
    if n <= 0: raise ValueError()
    l = []
    while n > 0:
        c = n%10
        n = n//10
        l.append(c)
    for i in range(len(l) - 1):
        l[i + 1] += l[i]
    return l[-1]

def testF():
    try:
        f(-1)
        assert False
    except ValueError:
        assert True

    assert f(123) == 6
    assert f(1) == 1

testF()