#cautari/sortari
#merge/bingo
# O(n*log(n))-time, O(n) - memory
def mergeSort(iterable, key=lambda x: x, cmp=lambda x, y: x < y, reverse=False):
    if reverse:
        reverse = lambda x: not x
    else:
        reverse = lambda x: x

    mergeSortUtil(iterable, key, cmp, reverse, 0, len(iterable) - 1)
    return iterable


def mergeSortUtil(iterable, key, cmp, reverse, start, end):
    if end-start < 1:
        return
    mid = (start + end) // 2
    mergeSortUtil(iterable, key, cmp, reverse, start, mid)
    mergeSortUtil(iterable, key, cmp, reverse, mid + 1, end)
    merge(iterable, start, mid, end, key, cmp, reverse)


def merge(iterable, start, mid, end, key, cmp, reverse):
    len_start = mid - start + 1
    len_end = end - mid

    start_list = iterable[start:(mid + 1)]
    end_list = iterable[(mid + 1):(end + 1)]

    index_start = 0
    index_end = 0
    index_all = start

    while index_start < len_start and index_end < len_end:
        if reverse(cmp(key(start_list[index_start]), key(end_list[index_end]))):
            iterable[index_all] = start_list[index_start]
            index_start += 1
        else:
            iterable[index_all] = end_list[index_end]
            index_end += 1
        index_all += 1

    while index_start < len_start:
        iterable[index_all] = start_list[index_start]
        index_all += 1
        index_start += 1

    while index_end < len_end:
        iterable[index_all] = end_list[index_end]
        index_all += 1
        index_end += 1


def bingoSort(iterable, key=lambda x: x, cmp=lambda x, y: x < y, reverse=False):
    if reverse:
        reverse = lambda x: x
    else:
        reverse = lambda x: not x

    last = len(iterable) - 1
    nextMax = iterable[last]

    for i in range(last - 1, -1, -1):
        if reverse(cmp(key(iterable[i]), key(nextMax))):
            nextMax = iterable[i]

    while last > 0 and iterable[last] == nextMax:
        last -= 1

    while last:
        prevMax = nextMax
        nextMax = iterable[last]

        for i in range(last - 1, -1, -1):
            if reverse(cmp(key(iterable[i]), key(nextMax))):
                if iterable[i] != prevMax:
                    nextMax = iterable[i]
                else:
                    iterable[i], iterable[last] = iterable[last], iterable[i]
                    last -= 1

        while last > 0 and iterable[last] == nextMax:
            last -= 1

    return iterable