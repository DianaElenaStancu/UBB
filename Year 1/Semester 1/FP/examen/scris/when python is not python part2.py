"""
a, b = 1, 2
l = [a, b]#[1,2]
a = 7
l2 = [a]#[7]
l.append(l2)#[1,2,[7]]
l2[0] = 8 #[8]
print(a, l2, l)#7, [8], [1,2,[8]]

#--------------------------------------
print("***************")

def f(i):
 return i + 1

def g(h):
 return h(1)

def h(x):
 return x + 10

i = lambda x:x + 2
print(f(f(f(g(i)))))

g(i) = i(1) = 3
f(g(i)) = f(3) = 4
f() = 5
f() = 6
"""

#--------------------------------------
print("***************")
"""
def f():
 return 1
def g(x=1):
 return x + 1
def h(x=1, y=2):
 return x + y
l = [f, g, h]
for e in l:
 print(e())
h = lambda x = 1, y = 2: x * y
print(l[2](3), h(), h(3), h(x=3), h(y=3))
print(h([2, 3]))
print(h(*[2, 3])) #desparte elementele

1
2
3
5 2 6 6 3
[2, 3, 2, 3]
6
"""

"""class A:
 def f(self):
  return 1

def g():
 return 2

a = A()
a.f = g

a2 = A()
A.f = lambda x: 3
l = [a, a2, A()] #[2, 3,3]
for e in l:
 print(e.f())
"""
 #----------------------
"""s = 0
def f(x):
 global s
 if x > 1:
  s = s + x
  f(x - 1)
 s = s + x

f(3)
print(s)"""

class A:
 def __init__(self, k):
  self.__k = k
  self.__items = []
 def add(self, a):
  self.__items.append(a)
  return self
 def f(self, l):
  if l == 0:
   print (self.__k)
  for a in self.__items:
   a.f(l - 1)

a = A(1)
a.add(A(2))
a.add(A(3).add(A(5).add(A(7))))
a.add(A(4).add(A(6)))
a.f(2)