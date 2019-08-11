#'Jump to Python' Chapter 4_Function, Question 1

def fib(n):
    print(n, end = ' ')
    if n == 0:
        return 0
    elif n == 1:
        return 1
    return fib(n-2) + fib(n-1)

