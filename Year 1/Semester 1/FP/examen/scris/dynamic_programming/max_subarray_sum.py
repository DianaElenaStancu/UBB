def max_subarray_sum(A):
    # suma maxima obtinuta pentru solutia care se termina pe pozitia i
    max_i = A[0]

    # suma maxima generala
    max_overall = A[0]

    for i in range(1, len(A)):
        # pentru elementul A[i] exista 2 variante:
        # fie iau si elementele de dinaintea lui, i.e. suma maxima care se termina cu elementul
        # de pe pozitia anterioara (max_so_far + element_curent)
        # fie `pornesc` cu o noua suma - nu ma ajuta sa iau elementele din urma
        # i.e. genereaza o suma mai mica decat daca as lua doar (sublista formata din)
        # elementul curent

        # verific care varianta genereaza cea mai mare suma
        # - solutie optima pentru fiecare pozitie i
        max_i = max(A[i], max_i + A[i])

        # verific daca suma gasita pana acum e mai mare decat suma maxima generala
        max_overall = max(max_i, max_overall)

    return max_overall


def test_max_subarray_sum():
    A1 = [-2, -5, 6, -2, -3, 1, 5, -6]
    # subarray cu suma maxima: [6, -2, -3, 1, 5]
    assert (max_subarray_sum(A1) == 7)

    A2 = [1, 2, 3, 4]
    # subarray cu suma maxima: [1,2,3,4]
    assert (max_subarray_sum(A2) == 10)

    A3 = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    assert (max_subarray_sum(A3) == 6)
