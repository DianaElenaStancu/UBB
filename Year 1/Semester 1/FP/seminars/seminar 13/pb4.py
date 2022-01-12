"""
BACKTRACKING
    DESCRIEREA SOLUTIEI
        SOLUTIA CANDIDAT
            configuratie partiala care poate sau nu conduce la solutie
            x = (x0, ..., xk), xi e Di

        CONDITIE CONSISTENTA
            fct care verifica daca o configuratia partiala poate conduce la o solutie

        CONDITIE SOLUTIE
            fct care verifica daca o solutie candidat este solutia finala/ceruta

    se da un cuvant format din litere distincte
    sa se genereze anagramele lui in ord alfabetica
    ex:rac
       acr
       arc
       car
       cra
       rac
       rca

    Solutie candidat:
        x = (x0, x1, ..., xk), xi e A = mt literelor cuv dat
        k < len(cuv)

    Conditie consistenta:
    x = (x0, ...., xk) e consistent daca xi != xj, pentru orice i, j

    Conditie solutie:
    x = (x0, ..., xk) solutie daca e consistenta si k  = len(cuv) - 1
"""
    #cuv este sortat
    def back_rec(x, cuv):
        x.append(-1)
        for litera in cuv:
            x[-1] = litera
            if consistent(x):
                if solution(x):
                    afiseaza(x)
                else:
                    back_rec(x[:], cuv)

