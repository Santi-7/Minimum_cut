#!/usr/bin/env python

import sys
import random


n = int(sys.argv[1])

print n
print

for i in range(1, n + 1):
    print "product" + str(i)

print

for i in range(1, n + 1):
    j = i + 1
    while j < n + 1:
        if random.random() > 0.5:
            print "product" + str(i) + " | product" + str(j)    
        j += 1

