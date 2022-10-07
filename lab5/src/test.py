import random

TEST_NUM = 1000000
letters = "".join([random.choice('abcdefghijklmnopqrstuvwxyz') for i in range(1000)])

with open("tests.txt", 'w') as f:
    f.write(letters + "\n")
    for i in range(TEST_NUM):
        rofl = random.randint(0, 1)
        if rofl:
            num1 = random.randint(0, len(letters) - 1)
            num2 = random.randint(num1 + 1, len(letters))
            f.write(letters[num1:num2] + "\n")
        else:
            f.write("".join([random.choice('abcdefghijklmnopqrstuvwxyz') for i in range(20)]) + "\n")