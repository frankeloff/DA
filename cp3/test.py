TEST_LETTERS = 500000

with open("test.txt", "w") as f:
    f.write("compress\n")
    result_str = ""
    for i in range(TEST_LETTERS):
        if i%2==0:
            result_str += "b"
        else:
            result_str += "a"
    f.write(result_str)

# TEST_COUNT = 1000000
# with open("test.txt", "w") as f:
#     f.write("decompress\n")
#     f.write("0 0 a\n")
#     f.write("0 0 b\n")
#     my_range = TEST_COUNT - 2
#     f.write(f"1 {my_range} a")
