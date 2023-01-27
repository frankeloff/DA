from random import randint

MAX_LEN = 1000000
res = ''
with open('test.txt', 'w') as f:
    f.write(str(MAX_LEN) + '\n')
    for i in range(MAX_LEN):
        res += str(randint(1, 3)) + ' '

    f.write(res)