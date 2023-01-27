def encode(word, result):
    global_pos = 0

    while(global_pos < len(word)):
        if global_pos == 0:
            result.append((0,0,word[global_pos]))
            global_pos += 1
        else:
            max_size = 0
            shift = 0
            for i in range(global_pos):
                j = i
                local_size = 0
                while j - i + global_pos < len(word) and word[j] == word[global_pos + j - i]:
                    local_size += 1
                    j += 1
                if local_size >= max_size and local_size > 0:
                    max_size = local_size
                    shift = global_pos - i
            if global_pos + max_size > len(word) - 1:
                result.append((shift, max_size, " "))
            else:
                result.append((shift, max_size, word[global_pos + max_size]))
            global_pos += max_size + 1
                
def decode(result):
    res_arr = []
    i = 0
    for res in result:
        if res[0] > 0:
            for _ in range(res[1]):
                res_arr.append(res_arr[i - res[0]])
                i += 1
            res_arr.append(res[2])
            i += 1
        else:
            res_arr.append(res[2])
            i += 1
    print("".join(map(str, res_arr)))



# word = input()
result = []
# if word == "compress":
# encode("abababbbabba", result)
# print(result)

decode(((0,0,"a"), (0, 0, "b"), (0, 0, "r"), (3, 1, "c"), (2, 1, "d"), (7, 4, " ")))
    