n=int(input())
m=n
value=0
while m>0:
    m-=1
    value+=1
print("yes" if n==value else "no")