def cifraInNumar(numar, cifra):
    while numar > 0:
        if numar%10 == cifra:
            return True
        numar = numar//10
    return False