import os

data = int(input("ㅜ하려는 소수 개수 : "))

prime = True
num = 2
k = 0
while k < data:
    for i in range(2, num):
        prime = True
        if num % i == 0:
            prime = False
            num += 1
            break

    if prime == True:
        print(num)
        k += 1
        num += 1
