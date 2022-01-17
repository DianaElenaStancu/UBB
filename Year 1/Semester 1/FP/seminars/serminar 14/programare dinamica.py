"""
programare dinamica

-structura sol
-relatia de recurenta


longest increasing subsequence
A = [2, 5, 1, 8, 3]
- 2, 5, 8


l =
li - lg max a ubsecv care se termina cu p

pi = indicele elem prec din subsecv care se termina in A[i]


"""
def longest(A):
    p = [-1]
    l = [1]
    max_l = 0
    best_end = -1
    for i in range(1, len(A)):
        l.append(1)
        p.append(-1)
        for j in range(i-1, -1, -1):
            if l[j] + 1 > l[i] and A[i] > A[j]:
                l[i] = l[j] + 1
                p[i] = j
        if l[i] > max_l:
            max_l = l[i]
            best_end = i
    rez = []
    while best_end != 1:
        rez.append(A[best_end])
        best_end = p[best_end]
    rez.reverse()



