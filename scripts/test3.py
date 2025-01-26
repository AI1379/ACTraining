def f(n):           
    result=[3,4]    
    for i in range(n-2):
        result.append(result[-2]+result[-1]+2)
    return result[-1]  

print(f(5))  