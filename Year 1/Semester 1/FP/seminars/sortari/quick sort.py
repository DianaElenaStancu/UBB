def partition(l,left,right):
 """
 Split the values:
 smaller pivot greater
 return pivot position
 post: left we have < pivot
 right we have > pivot
 """
 pivot = l[left]
 i = left
 j = right
 while i!=j:
  while l[j]>=pivot and i<j:
   j = j-1
  l[i] = l[j]
  while l[i]<=pivot and i<j:
   i = i+1
  l[j] = l[i]
 l[i] = pivot
 print(i)
 print(l)
 print("*********************")
 return i


def quickSortRec(l,left,right):
 #partition the list
 pos = partition(l, left, right)
 #order the left part
 if left<pos-1:
  quickSortRec(l, left, pos-1)
 #order the right part
 if pos+1<right:
  quickSortRec(l, pos+1, right)


l = [10, 80, 30, 90, 40, 50, 70]
quickSortRec(l, 0, len(l) - 1)
print(l)