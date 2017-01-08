#!/usr/bin/env python3

import sys
import random

if len(sys.argv) < 5:
	print("Usage: ./graphGen.py verticesLeft verticesRight mincut density")
	exit(1)
addWeight = 0
if len(sys.argv) == 6:
	addWeight = int(sys.argv[5])

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
				if addWeight != 0:
					print(vertex, '|',  j, '|', random.randint(1, addWeight))
				else:
					print(vertex, '|', j)
				edges += 1
			j += 1
		if edges == 0 and vertex != vertices[-1]:
			if addWeight != 0:
				print(vertex, '|', vertex + 1, '|', random.randint(1,addWeight))
			else:
				print(vertex, '|', vertex + 1)
	print()
if addWeight == 0:
	for _ in range(mincut):
		print(random.randint(0,verticesLeft-1), '|', random.randint(verticesLeft, verticesLeft + verticesRight -1))
else:
	cutweight = 0
	while cutweight < mincut:
		edgeweight = random.randint(1, mincut - cutweight)
		cutweight += edgeweight
		print(random.randint(0,verticesLeft-1), '|', random.randint(verticesLeft, verticesLeft + verticesRight -1), '|', edgeweight)

