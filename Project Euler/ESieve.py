def primes_sieve(limit):
    a = [True] * limit
    a[0] = a[1] = False

    result = []

    for (i, isprime) in enumerate(a):
        if isprime:
            result.append(i)

            for n in range(i*i, limit, i):
                a[n] = False

    return result

