import random

num = ''
with open('test.txt', 'w') as f:
    for i in range(3):
        num += str(random.randint(1,9))
    f.write(num)

