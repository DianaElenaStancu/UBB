"""
se da un nr natural de cel mult 9 cifre. sa se afiseze toate modalitatile prin care se poate scrie
ca produsde div. proprii


ex: 30 = 2*3*5 = 2*15 = 3*10 = 5*6

Solutie candidat
    x = (x0, .., xk), xi e Dn = {d| n:d}

Conditie consistenta
    x = (x0, ...., xk)
Conditie solutie
    x = (x0, ..., xk) consistent daca produsul tutor <= n si x0 < x1 < ... < xk
Conditie Solutie
    x = (x0, ..., xk) sol daca produsul = n
"""
"""
se genereaza permuarile cu eleme de la 1 la n in care valorile pare sunt pe pozitii fixe

solutie candidat
x = (x0, ..., xk), xi e {1, ..., n}

conditie consistenta
x = (x1, .., xk) consist daca i, i%2 == 0, xi = i
si orice i, j xi != xj

conditie solutie


"""