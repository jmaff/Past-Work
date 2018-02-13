import ESieve

primes_list = ESieve.primes_sieve(100000)


def is_truncatable_prime(n):
    num = str(n)

    while len(num) > 1:
        if int(num) in primes_list:
            num = num[:-1]
        else:
            return False

    while len(num) > 1:
        if int(num) in primes_list:
            num = num[1:]
        else:
            return False

    return True


counter = 0
total = 0
x = 10

while counter < 11:
    if is_truncatable_prime(x):
        total += x
        counter += 1

    x += 1

print(is_truncatable_prime(29))