import random, string

with open("text.txt", 'w') as f:
    a = ''.join([random.choice(string.ascii_lowercase + string.digits) for i in range(64)])
    for i in range(100000):
        f.write(f'{random.randint(0, 10000000)}    {a}\n')
