#writedata.py
f = open("Hello.txt", "w")
for i in range(1,11):
    data = "Line %d\n" %i
    f.write(data)
f.close()