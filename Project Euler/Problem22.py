def convert_char(old):
    if len(old) != 1:
        return 0
    new = ord(old)
    if 65 <= new <= 90:
        # Upper case letter
        return new - 64
    elif 97 <= new <= 122:
        # Lower case letter
        return new - 96
    # Unrecognized character
    return 0


f = open('problem-22-names.txt', 'r')
names = f.read()

names = names.replace('"', '')
names = names.split(',')
names.sort()

totalScore = 0

for i in range(len(names)):
    alphScore = 0
    for x in names[i]:
        alphScore += convert_char(x)

    rank = i + 1
    score = alphScore * rank
    totalScore += score

print(totalScore)

# SOLVED 11/16/17
