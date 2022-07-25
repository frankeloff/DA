import random
import string

MAX_TEST = 10000
MAX_LENGTH = 100
MAX_PATTERN = MAX_LENGTH//10

with open("output.txt", 'w') as f:
    for i in range(MAX_TEST):
        str = 'a'*MAX_LENGTH
        pattern = 'a'*MAX_PATTERN
        f.write(str + '\n')
        f.write(pattern + '\n')
