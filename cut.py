#!/usr/bin/env python3
import sys
import random

def readfile(filename):
	with open(filename) as f:
		edgelist = []
		nodelist = [] 
		nodenamelist = {}
		lines = f.readlines()
		counter = 1
		nodenum = int(lines[0])
		i = 1
		while counter <= nodenum:
			line = lines[i].rstrip().strip()
			print(line)
			if len(line) >= 1: 
				nodenamelist[line] = counter
				nodelist.append([counter])
				counter += 1
			i += 1 

		while i < len(lines):
			line = lines[i]
			if "|" in line:
				nodenameA = line.split('|')[0].rstrip().strip()
				nodenameB = line.split('|')[1].rstrip().strip()
				edgelist.append([nodenamelist[nodenameA], nodenamelist[nodenameB]])
			i += 1

	return edgelist, nodelist, nodenamelist
if len(sys.argv) < 2:
    exit(1)
edges, nodelist, names = readfile(sys.argv[1])
print("Initial node list: ", nodelist, "\nInitial edge list: ", edges)
random.shuffle(edges)
while(len(nodelist) > 2):
	selectededge = edges[0]
	absorbingnode = selectededge[0]
	decayingnode = selectededge[1]
	print("Absorbing node ", decayingnode, " into ", absorbingnode)
	for i in range(len(nodelist)):
		nodes = nodelist[i]
		if absorbingnode == nodes[0]:
			absorbingnodeindex = i
		elif decayingnode == nodes[0]:
			decayingnodeindex = i
	print("The node was ", nodelist[decayingnodeindex], " and will be inserted into ", nodelist[absorbingnodeindex])
	#print(len(nodelist), absorbingnodeindex, decayingnodeindex)
	nodelist[absorbingnodeindex].extend(nodelist[decayingnodeindex])
	del nodelist[decayingnodeindex]
	print("The new node list is: ", nodelist)
	del edges[0]
	print("Now to rename the edge list which begins as:\n", edges)
	edgeindicestodelete = []
	# Rename all node references for the decayed node to the absorbing one
	for i in range(len(edges)):
		if edges[i][0] == decayingnode:
			edges[i][0] = absorbingnode
		elif edges[i][1] == decayingnode:
			edges[i][1] = absorbingnode
	
	edges = [edge for edge in edges if edge[0] != edge[1]]
			
	print("Edge list: \n", edges) 
	print("----------------------\n")
	
print("The final list is: \n", nodelist, "\nAnd the cut found is: ", len(edges))

