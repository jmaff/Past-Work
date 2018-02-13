import ESieve


def get_rotations(n):
    num = str(n)
    rotlist = []
    i = 0

    while i < len(num):
        num = num[1:] + num[0]
        rotlist.append(int(num))
        i += 1

    return rotlist


primes_list = ESieve.primes_sieve(1000000)
total = 0

for x in primes_list:

    for digit in str(x):
        if x % 2 == 0:
            break
    else:
        if all(y in primes_list for y in get_rotations(x)):
            total += 1

print("There are " + str(total) + " circular primes under 1 million")

# SOLVED 2/9/18 (insanely slow however)
