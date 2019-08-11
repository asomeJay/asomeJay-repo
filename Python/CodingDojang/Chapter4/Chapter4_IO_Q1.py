# 'Jump to Python' Chapter 4_File IO, Question 1
f = open("sample.txt", "r")
lines = f.readlines()
f.close()

total = 0
for line in lines:
    score = int(line)
    total += score

average = float(total / len(lines))

f = open("result.txt", "w")
f.write(average)
f.close()
