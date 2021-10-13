"""Palindromul unui număr este numărul obținut prin scrierea cifrelor in ordine
 inversa (Ex. palindrom(237) = 732). Pentru un n dat calculați palindromul sau."""

n = int(input())
n_str = str(n)
n_str = n_str[8:1:-1]
n_int = int(n_str)
print(n_str)
"""n_str = n_str[::-1]
"""
