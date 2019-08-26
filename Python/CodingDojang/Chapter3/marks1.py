# marks1.py
marks = [90, 25, 67, 45, 80]
number = 0
for mark in marks:
    number += 1
    if mark >= 60:
        print("Student %d Passes." %number)
    else:
        print("Student %d Fails." %number)

