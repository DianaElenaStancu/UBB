import m1

a = 2
def g():
    global a
    a = m1.f(3) + 1
    return m1.h()

print(g(), a)