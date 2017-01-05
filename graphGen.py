#!/usr/bin/env python3

import sys
import random

if len(sys.argv) < 5:
    print("Usage: ./graphGen.py verticesLeft verticesRight mincut density")
    exit(1)

verticesLeft = int(sys.argv[1])
verticesRight = int(sys.argv[2])
mincut = int(sys.argv[3])
density = float(sys.argv[4])
print(verticesLeft + verticesRight)

print(*range(verticesLeft + verticesRight), sep='\n')
print()
for vertices in [range(verticesLeft), range(verticesLeft, verticesLeft + verticesRight)]:
    for vertex in vertices:
        j = vertex + 1
        edges = 0
        while j <= vertices[-1]:
            if random.random() < density:
                print(vertex, '|',  j)
                edges += 1
            j += 1
        if edges == 0 and vertex != vertices[-1]:
            print(vertex, '|', vertex + 1)
    print()

for _ in range(mincut):
    print(random.randint(0,verticesLeft-1), '|', random.randint(verticesLeft, verticesLeft + verticesRight -1))
