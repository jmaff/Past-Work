d = ""
x = 0

while len(d) <= 1000000:
    d += str(x)
    x += 1

result = int(d[1]) * int(d[10]) * int(d[100]) * int(d[1000]) * int(d[10000]) * int(d[100000]) * int(d[1000000])
print(result)

# SOLVED 2/9/18
