from pprint import pprint

import numpy as np


def longest_common_subsequence(a, b):
    tabel = np.zeros((len(a) + 1, len(b) + 1))

    # construim un tabel de dimensiune lungime_a + 1 x lungime_b +1
    # +1 pentru ca punem un rand si o coloana de 0 ca sa avem de unde porni
    # tabel[i,j] = lungimea subsecventei maxime dintre a[:i] si b[:j]

    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                tabel[i, j] = 1 + tabel[i - 1, j - 1]
            else:
                tabel[i, j] = max(tabel[i - 1, j], tabel[i, j - 1])

    print('Tabelul construit este:')
    print(tabel)
    return tabel.max()


def test_longest_common_subseq():
    s1 = 'abc'
    s2 = 'ajdfhbsdkfj'
    assert (longest_common_subsequence(s1, s2) == 2)

    s1 = 'abc'
    s2 = 'fjdbhgdfsgjka'
    assert (longest_common_subsequence(s1, s2) == 1)

    s1 = 'abc'
    s2 = 'cbakfdssbc'
    assert (longest_common_subsequence(s1, s2) == 3)

    s1 = 'abc'
    s2 = 'cbkfdssbc'
    assert (longest_common_subsequence(s1, s2) == 2)

    s1 = 'abbbc'
    s2 = 'cbsfbsfjsbbbc'
    assert (longest_common_subsequence(s1, s2) == 4)

    s1 = 'abbbc'
    s2 = 'cbsfbsfjsbc'
    assert (longest_common_subsequence(s1, s2) == 4)

    s1 = 'abbbc'
    s2 = 'csfsfbjsbc'
    assert (longest_common_subsequence(s1, s2) == 3)

test_longest_common_subseq()