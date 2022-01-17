"""
w - overwrites, create file if doesn't exist
a - append, same
r - read, open file for read
"""

with open("test.txt", "w") as f:
    f.write("var lavabil de lavanda")

with open("test.txt", "r") as f:
    for linie in f:
        print(linie)

with open("test.txt", "a") as f:
    f.write("hai sa mancam clatite")

with open("test.txt", "r") as f:
    for linie in f:
        print(linie)

with open("test.txt", "w") as f:
    f.write("hai sa mancam clatite")

with open("test.txt", "r") as f:
    for linie in f:
        print(linie)