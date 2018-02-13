# Top right corner is an odd perfect square, 1001**2 is the highest as the spiral is 1001x1001
diagonals = [[x**2] for x in range(1, 1002) if x % 2 != 0]

for i, v in enumerate(diagonals):
    if v[0] == 1:
        continue
    for j in range(3):
        v.append(v[-1] - (2*i))
# flatten list of lists of corners
diagonals = [item for sublist in diagonals for item in sublist]
print(sum(diagonals))

# SOLVED 11/19/17
