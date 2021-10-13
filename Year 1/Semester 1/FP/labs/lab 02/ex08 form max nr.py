"""Pentru un număr natural n dat găsiți numărul natural maxim m format cu
 aceleași cifre. Ex. n=3658, m=8653."""

dig_string = input()
dig_map = map(int, dig_string)
dig_list = list(dig_map)
dig_list.sort(reverse = True) 
string_list = [str(digit) for digit in dig_list] #!!!!!
fin_string = "".join(string_list)
number = int(fin_string)
print(number)


""""
map(fun, iter)
fun : It is a function to which map passes each element of given iterable.
iter : It is a iterable which is to be mapped.
Returns a list of the results after applying the given function  
to each item of a given iterable (list, tuple etc.)


lambda arguments: expression

lista = list(map - object)


list.sort(reverse=True|False, key=myFunc)
"??".join(string_list)
"""
