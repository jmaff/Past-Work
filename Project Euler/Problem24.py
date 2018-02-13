import itertools


def get_permutations(num):
    digits = [int(x) for x in str(num)]
    permutations = itertools.permutations(digits)
    permutations = [x for x in permutations]

    return list(map(int, [''.join((map(str, i))) for i in permutations]))


print(get_permutations('0123456789')[999999])

# SOLVED 11/19/17
