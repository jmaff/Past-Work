

rows = []
with open('problem-18-data') as f:
    for line in f:
        rows.append([int(i) for i in line.rstrip('\n').split(" ")])

# data stored in file problem-18-data


def greatest_path(data, rowNum):
    for i in range(len(data[rowNum])):
        data[rowNum][i] += max(data[rowNum+1][i], data[rowNum+1][i+1])

    if len(data[rowNum]) == 1:
        return data[rowNum][0]

    else:
        return greatest_path(data, rowNum-1)


print(greatest_path(rows, len(rows)-2))

# SOLVED 11/16/17
