NUM_COUNT = 50001
ROW_COUNT = NUM_COUNT - 1
count = 1

with open('test.txt', 'w') as f:
    f.write(f'{NUM_COUNT} {ROW_COUNT}' + '\n')
    for i in range(ROW_COUNT):
        f.write(f'{count} {count+1}' + '\n')
        count += 1