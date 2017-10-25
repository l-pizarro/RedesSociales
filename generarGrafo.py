from random import *
r = open("Entrada.txt" , "w");

r.write("100\n")

for x in range (1, 101):
    for y in range(1, 101):
        r.write(str(x) + " " + str(y) + "\n");

r.close();
