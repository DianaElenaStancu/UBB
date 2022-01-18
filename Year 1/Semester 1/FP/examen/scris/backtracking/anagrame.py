def consistent(x):
    if len(set(x)) == len(x):
        return True
    return False


def anagrame_rec(x, word):
    x.append('')
    for character in sorted(word):
        x[-1] = character
        if consistent(x):
            if len(x) == len(word):
                print('[BACKTRACKING RECURSIV] Solutie:', ''.join(x))
            else:
                anagrame_rec(x[:], word)
    x.pop()


def anagrame_iterativ(word):
    sword = [' ']
    sword.extend(sorted(word))
    word_len = len(word)

    x = [' ']

    while len(x) > 0:
        chosen = False
        while not chosen and sword.index(x[-1]) < len(word):
            x[-1] = sword[sword.index(x[-1]) + 1]
            chosen = consistent(x)

        if chosen:
            if len(x) == word_len:
                print('[BACKTRACKING ITERATIV] Solutie:', ''.join(x))
            else:
                x.append(' ')
        else:
            x = x[:-1]


anagrame_rec([], 'rac')
print()
anagrame_iterativ('rac')
