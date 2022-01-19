#1
def f1(l, n):
    l = l + [n]
def g1(l):
    l *= 2
def h1(l, n):
    l.extend([n])
def ml():
    l = [1,2]
    n = 3
    f1(l, n)
    print(l)#[1,2]
    g1(l)
    print(l)#[1,2,1,2]
    h1(l, 3)#[1,2,1,2,3]
    print(l)
ml()

#=================================
#2
def f2(l):
    l.clear()
    l.append(10)
def g2(l):
    l = []
    l.append(10)
def h2(k):
    k += 1

def m2():
    lf = [1,2,3]
    lg = [1,2,3]
    n = 0
    f2(lf)#[10]
    g2(lg)#[1,2,3]
    h2(n)#0
    print(lf, lg, n)

m2()

#================================
#3
l = [1,2]
l2 = [3]
def f3(n):
    l2 = l[:]
    l.append(n)
f3(5)
print(l, l2)#[1,2,5], [3]


#==================================
#4
def p1():
    a = 1
    n = a# n = 1
    b = [a] + [0] # b = [1, 0]
    c = [1] + [b] # c = [1, [1,0]], [1,0] va fi adresa catre b, orice modificare in b o sa fie si in c si vice versa
    c.append(a) # c = [1,[1,0],1]
    a = 0 #0
    b[1] = 2 # b = [1,2]
    c[1][0] = 3 # c= [1,[3,2],1]
    print(a, b, c, n)
    # 0, [3,2], [1,[3,2],1], 1
p1()

#===========================================
#5
def p2():
    a = lambda x: x + 1
    b = lambda x: x + [1]
    c = b([2]) # c = [2,1]
    d = [a,b,c] # d= [a, b, [2,1]]
    print(a(2), b([2])) #3,[2,1]
    a = [3,4]
    b = [5,6]
    c = [7,8] #d = [a, b, [2,1]]
    print(d[0](2)) #3
    print(d[2][0]) #2
p2()

#=======================
#6
def g3(n):
    return n + 1
def f3(x, y):
    return x(y) + 1

print(f3(g3, 1)) # = g3(1) + 1 = 2+1 = 3
b = [f3, g3]
a = lambda x:x + 2
print(a(1))#3
print(g3(a(1)))#4
g3 = a#SE CREEAZA UN NOU OBIECT
print(b)#[f3, g3]
print(b[1](1))#2