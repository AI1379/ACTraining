def bubble_sort(nums):
    # 这个循环负责设置冒泡排序进行的次数
    rst=0
    for i in range(len(nums) - 1):  
        for j in range(len(nums) - i - 1):  # j为列表下标
            if nums[j] > nums[j + 1]:
                nums[j], nums[j + 1] = nums[j + 1], nums[j]
        if i==0 or i==3:
            rst=rst+nums[5]
    return rst
 
print(bubble_sort([45, 32, 8, 33, 12, 22, 19, 97]))