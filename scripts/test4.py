a=[5,16,39,45,51,98,100,202,226,321,368,444,501]
x = int(input())
found = -1
left = 0                      #第一个元素下标
right = len(a)-1              #最后一个元素下标
while left<=right:
    mid = (left + right) // 2
    if a[mid] > x:
        right = mid - 1
    elif a[mid] < x:
        left = mid + 1
    else:                     # a[mid]==x
        found = mid
        break
print(left)