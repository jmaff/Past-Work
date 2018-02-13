def get_bin(n):
    return str(bin(n)[2:])


result = 0
for i in range(1000000):
    if str(i) == str(i)[::-1] and get_bin(i) == get_bin(i)[::-1]:
        result += i

resultString = "The sum of all numbers less than one million that are palindromic in base 10 and 2 is: {}".format(result)
print(resultString)

# SOLVED 2/9/18

