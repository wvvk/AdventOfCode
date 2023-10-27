import string

#Winnie Kam

lower_upper_alphabets = string.ascii_lowercase + string.ascii_uppercase
# print (lower_upper_alphabets)

char_val_map = {}
val_index = 1
for c in lower_upper_alphabets:
    char_val_map[c] = val_index
    val_index += 1
# print (char_val_map)

sum_of_common = 0
with open("backpacks.txt", "r") as f:
    file_contents = f.read()
    # print(line)
    lines = file_contents.split('\n')
    for line in lines:
        line_len = len(line)
        front_set = set()
        back_set = set()
        character_list = [c for c in line]
        # print(character_list)
        front_set.update(character_list[: int(line_len / 2)])
        back_set.update(character_list[int(line_len / 2):])
        common_char = front_set.intersection(back_set)
        # if (len(common_char)!=1):
        #    print("ERROR: len not 1")
        common_char = common_char.pop()
        #       print(common_char)
        sum_of_common += char_val_map[common_char]

print("sum_of_common: " + str(sum_of_common))
