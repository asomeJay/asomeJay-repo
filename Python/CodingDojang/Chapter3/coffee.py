#coffee.py
coffee = 10
while 1:
    money = int(input("Give me the money : "))
    if money == 300:
        print("Give you coffee")
        coffee -= 1

    elif money > 300:
        print("Give you coffee and Change %d" %(money - 300))
        coffee -= 1

    else :
        print("Give you all money ")
        print("%d coffee is being" %coffee)

    if not coffee:
        print("The coffee runs out\n")
        print("Closing\n")
        break

