def specialSum(l, left, right):
    if left == right:
        if left%2 == 1 and l[left]%2 == 0:
            return l[left]
        return 0
    mid = (left+right)//2
    return specialSum(l, left, mid) + specialSum(l, mid + 1, right)


l = [1,2,3,4,5]
print(specialSum(l, 0, len(l)-1))