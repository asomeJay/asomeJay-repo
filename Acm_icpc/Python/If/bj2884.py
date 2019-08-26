# bj2884.py

# 0 <= H <= 23, 0 <= M <= 59

H, M = map(int,input().split(" "))

if M < 45:
    if H == 0:
        H = 24
    M += 60
    H -= 1

print("%d %d" %(H, M-45))


"""
a,b=map(int,input().split())
print((a-(b<45))%24,(b-45)%60)
"""