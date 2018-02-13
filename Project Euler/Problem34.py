import math


def sum_of_digit_factorials(n):
    digits = [math.factorial(int(x)) for x in str(n)]

    return sum(digits)


factorions = [i for i in range(3, 50000) if sum_of_digit_factorials(i) == i]

print(sum(factorions))

# SOLVED 11/19/17
