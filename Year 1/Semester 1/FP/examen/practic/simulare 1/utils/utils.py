def existaCifra(numar, cifra):
    if numar == 0 and cifra == 0:
        return True
    while numar != 0:
        if numar%10 == cifra:
            return True
        numar = numar//10
    return False