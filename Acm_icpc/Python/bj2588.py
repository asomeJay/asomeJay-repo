# bj2588

number1 = int(input())
number2 = input()
temp = reversed(list(number2))


for i in temp:
    print("%d" %(number1 * int(i)))

print("%d" %(number1 * int(number2)))