primes = [7, 17, 19, 23, 29, 47, 59, 61, 97, 109, 113, 131, 149, 167, 179, 181, 193, 223, 229, 233, 257, 263, 269, 313,
          337, 367, 379, 383, 389, 419, 433, 461, 487, 491, 499, 503, 509, 541, 571, 577, 593, 619, 647, 659, 701, 709,
          727, 743, 811, 821, 823, 857, 863, 887, 937, 941, 953, 971, 977, 983]

"""primes that produce their cyclic number (from Wikipedia -> can also be computed by seeing 
 if the result itself has repeating numbers)"""


def fermat_quotient(b, p):  # finds the cyclic number of p, a prime, in the number base, b
    return int(b**(p-1)-1)//p


greatest = 0
result = 0

for i in primes:
    if fermat_quotient(10, i) > greatest:
        greatest = fermat_quotient(10, i)
        result = i

print(result)

# SOLVED 11/17/17
