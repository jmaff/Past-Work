import time
from ESieve import primes_sieve
import math


def sumOfFactors(number, primelist):
    n = number
    total = 1
    p = primelist[0]
    j = 0
    i = 0

    while p * p <= n and n > 1 and i < len(primelist):
        p = primelist[i]
        i += 1
        if n % p == 0:
            j =  p * p
            n = n / p

            while n % p == 0:
                j = j * p
                n = n / p
                total = total * (j - 1) / (p - 1)

    return total


def sumOfFactors2(num):
    sqrtOfNum = int(math.sqrt(num))
    total = 1

    if num == sqrtOfNum ** 2:
        total += sqrtOfNum
        sqrtOfNum -= 1

    for i in range(2, sqrtOfNum):
        if num % i == 0:
            total = total + i + (num / i)

    return total


timeStart = time.time()

limit = 28123
abundant = []
prime_list = primes_sieve(int(math.sqrt(limit)))

for i in range(2, limit):
    if sumOfFactors2(i) > i:
        abundant.append(i)

canBeWrittenAsAbundant = [False] * (limit + 1)

# gets hung up here - need to find a solution other than brute forcing
result = 0
for num, isSum in enumerate(canBeWrittenAsAbundant):
    if not isSum:
        result += num

print(result)
print('Process took: ' + str(time.time()-timeStart))

