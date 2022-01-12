"""
    se da un nr natural
    sa se scrie toate configuratiile de cifre binare in care nu sunt 2 valori de 1 alaturate

    solutie candidat
        x = (x0, ..., xk), xi e {0,1}, k < n
    solutie consistent
        x = (x0, ..., xk) consistent daca xi*xi+1 != 1, orice i e {1, ...., k-1}
    conditie solutie
        x = (x0, ...., xk) soltie daca x consistent si k = n - 1
"""