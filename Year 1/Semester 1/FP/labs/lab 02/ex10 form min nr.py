"""Pentru un număr natural n dat găsiți numărul natural minim m format cu
 aceleași cifre. Ex. n=3658, m=3568."""

n_str = input()
n_map = map(int, n_str)
dig_list = list(n_map)
dig_list.sort()
str_list = [str(digit) for digit in dig_list]
ans = "".join(str_list)
ans_int = int(ans)
print(ans_int)
