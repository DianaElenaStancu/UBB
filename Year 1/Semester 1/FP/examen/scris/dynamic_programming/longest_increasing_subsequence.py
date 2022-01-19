def longest_increasing_subsequence(a):
    """
    Returneaza cea mai lunga subsecventa crescatoare dintr-o lista data
    :param a: lista in care se cauta subsecventa
    :type a: list of int
    :return: cea mai lunga subsecventa crescatoare din lista data
    :rtype: list of int
    """
    max_length = 1
    best_sequence_end = 0

    # l[i] reprezinta lungimea celei mai bune subsecvente care se termina cu a[i]
    l = [1]
    # p[i] reprezinta indexul elementului anterior din cea mai buna subsecventa care se termina in a[i]
    p = [-1]

    for i in range(1, len(a)):
        # initializam cu 1 l[i] curent (fiindca invariabil avem o
        # subsecventa de lungime 1 buna care se termina in a[i]
        # - e cea formata din elementul insusi)
        l.append(1)
        # initializam cu -1 p[i] curent fiindca deocamdata
        # avem doar subsecventa formata din elementul a[i],
        # nu exista element anterior
        p.append(-1)

        # j=i-1 inclusiv, 0
        for j in range(i - 1, -1, -1):
            # ne raportam la un element curent a[i]
            # parcurgem elementele de la i la inceputul listei
            # pentru care pe parcurs am memorat cele mai bune lungimi ale subsecventelor
            # care se termina cu ele

            # daca a[i]>a[j] - daca gasim un element a[j] mai mic decat
            # a[i] in lista a[0]...a[i-1] (conditia 1)
            # si daca lungimea subsecventei care se termina in a[j] + 1
            # (mai adaugam acelei subsecvente care se termina
            # in a[j] elementul curent a[i])
            # este mai mare decat cea mai buna lungime care am gasit-o pana acum prin acelasi proces
            # atunci memoram in l[i] noua lungime
            # si in p[i] punem indicele unde se gaseste in a
            # elementul precedent din aceasta subsecventa cea mai buna gasita
            if a[i] > a[j] and l[j] + 1 > l[i]:
                l[i] = l[j] + 1
                p[i] = j

        if l[i] > max_length:
            # salvam indicele la care se termina subsecventa de lungime maxima
            # pentru ca ulterior sa ne putem `intoarce` la inceputul ei parcurgand p[i]
            best_sequence_end = i
            max_length = l[i]

    rez = []
    i = best_sequence_end
    print(p)
    #formam subsecventa folosindu-ne de lista cu indici p
    while i != -1:
        rez.append(a[i])
        i = p[i]

    rez.reverse()
    return rez


longest_increasing_subsequence([1,2,3,1,5,3,4,1,4])

def test_longest_inc_subsequence():
    A1 = [3, 4, -1, 0, 6, 2, 3]
    assert (longest_increasing_subsequence(A1) == [-1, 0, 2, 3])

    A2 = [2, 5, 1, 8, 3]
    assert (longest_increasing_subsequence(A2) == [2, 5, 8])

    A3 = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
    assert (longest_increasing_subsequence(A3) == [0, 2, 6, 9, 11, 15])
