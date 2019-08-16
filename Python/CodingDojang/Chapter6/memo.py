import sys

option = sys.argv[1]
memo = sys.argv[2]

if option == '-a':
    f = open("memo.txt", 'a')
    f.write(memo + '\n')
    f.close()

elif option == '-v':
    f = open("memo.txt", "r")
    a = f.read();
    print(a)