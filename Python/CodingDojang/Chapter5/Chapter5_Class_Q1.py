# 'Jump to Python' Chapter 5_Class, Question 1

class Calculator:
    def __init__(self, list):
        self.Cal_list = list

    def sum(self):
        print(sum(self.Cal_list))

    def avg(self):
        print(sum(self.Cal_list)/ len(self.Cal_list))


cal1 = Calculator([1, 2, 3, 4, 5])
cal2 = Calculator([6, 7, 8, 9, 10])
