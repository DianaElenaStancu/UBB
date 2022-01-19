"""
pentru un n dat generati toate secventele de paranteze si acolade care se inchid corect

n = 4: 8 solutii:
    (())
    ()()
    {{}}
    {}{}
    {}()
    (){}
    {()}
    ({})

descriere solutie bkt:

solutie candidat:
x = (x0, x1, x2, ..., xk), xk < n
xi e { "{", "}", "(", ")"}

conditie consistenta:
x = (x0, x1, x2, ..., xk), xk < n
pentru orice i = 1,k, daca xi e {"}",")"}, exista j < i ai xj e {"{", "("}

conditie solutie:
x - consistent, k == n-1
"""

def consistent(x, n):
    if len(x) > n:
        return False
    stack1 = 0
    stack2 = 0
    for i in range(0, len(x)):
        if x[i] == "{":
            stack1 = stack1 + 1
        elif x[i] == "(":
            stack2 = stack2 + 1
        elif x[i] == "}":
            if stack1 > 0:
                stack1 -= 1
            else:
                return False
        elif x[i] == ")":
            if stack2 > 0:
                stack2 -= 1
            else:
                return False
    return True

def solutie(x, n):
    stack1 = 0
    stack2 = 0
    for i in range(0, len(x)):
        if x[i] == "{":
            stack1 = stack1 + 1
        elif x[i] == "(":
            stack2 = stack2 + 1
        elif x[i] == "}":
            if stack1 > 0:
                stack1 -= 1
            else:
                return False
        elif x[i] == ")":
            if stack2 > 0:
                stack2 -= 1
            else:
                return False
    return len(x) == n and stack1 == 0 and stack2 == 0

def backRec(x, n):
    x.append(0)
    for el in ["{", "(", "}", ")"]:
        x[-1] = el
        if consistent(x, n):
            if solutie(x, n):
                print(x)
            else:
                backRec(x, n)
    x.pop()

n = 4
backRec([], n)