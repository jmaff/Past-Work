triangle_numbers = [0.5*x*(x+1) for x in range(26*20)]


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


def is_triangle_word(word):
    value = 0
    for letter in word:
        value += convert_char(letter)

    return value in triangle_numbers


f = open('problem-42-words.txt', 'r')
words = f.read()
words = words.replace('"', '')
words = words.split(',')

result = 0

for word in words:
    if is_triangle_word(word):
        result += 1

print(result)

# SOLVED 9/2/18

