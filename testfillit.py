#!/usr/bin/python
from __future__ import print_function
import sys, random, os

for i in range(1000):
    n_tetro = random.randrange(1, 12)
    os.system("./random_tetriminos.py " + str(n_tetro) + "&& ./our_fillit ttmnfile > ourfillitlog" + str(i) + "&& ./fillit ttmnfile > fillitlog" + str(i) + "&& diff fillitlog" + str(i) + " ourfillitlog" + str(i) + " > diff" + str(i))
    os.system("echo -n" + str(i) + " && cat diff" + str(i))
