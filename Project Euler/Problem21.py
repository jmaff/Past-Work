

def sum_proper_divisors(num):
    result = 0
    for i in range(1, num):
        if num % i == 0:
            result += i
    return result


total = 0
for i in range(1, 10000):
    if i == sum_proper_divisors(sum_proper_divisors(i)) and i != sum_proper_divisors(i):
        print(i)
        total += i

print("Total: %s" % total)

# SOLVED 11/16/17



