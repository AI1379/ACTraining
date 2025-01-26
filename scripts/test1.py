a = [5, 16, 39, 45, 51, 98, 226, 321, 368, 444, 501]
x = int(input())
left = 0
right = len(a)-1
while left <= right:
    mid = (left + right) // 2
    if a[mid] > x:
        right = mid-1
    elif a[mid] < x:
        left = mid+1
    else:
        break
print(left)
