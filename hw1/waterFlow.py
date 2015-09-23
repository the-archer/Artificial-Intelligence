import sys, getopt
import pprint
from collections import deque
from heapq import *


def getInput(f1):
	algo = f1.readline().rstrip('\n')
	startnode = f1.readline().rstrip('\n')
	goalnodes = set(f1.readline().rstrip('\n').split())
	midnodes = set(f1.readline().rstrip('\n').split())
	graph = dict()
	graph[startnode] = []
	for node in goalnodes:
		graph[node] = []
	for node in midnodes:
		graph[node] = []

	pipes = int(f1.readline().rstrip('\n'))
	for i in range(0, pipes):
		line = f1.readline().rstrip('\n').split()
		start = line[0]
		end = line[1]
		length = int(line[2])
		offp = int(line[3])
		status = [True]*24
		for x in range(0, offp):
			interval = [int(x) for x in line[4+x].split('-')]
			for j in range(interval[0], interval[1]+1):
				status[j] = False
		graph[start].append([end, length, status])
	stime = int(f1.readline().rstrip('\n'))
	f1.readline()

	return algo, [startnode, goalnodes, graph, stime]



def runBFS(data):
	startnode = data[0]
	goalnodes = data[1]
	graph = data[2]
	stime = data[3]
	if startnode in goalnodes:
		return (startnode, stime)
	frontier = deque()
	frontier.append((startnode, stime))
	explored = set()
	while True:
		if len(frontier) == 0:
			return ("None",)
		#print (frontier)
		node = frontier.popleft()
		explored.add(node[0])
		for edge in sorted([x for x in graph[node[0]]]):
			child = (edge[0], (node[1]+1)%24)
			#print (child[0])
			if child[0] not in explored and child[0] not in [x[0] for x in frontier]:
				if child[0] in goalnodes:
					return child
				frontier.append(child)
				


def runDFS(data):
	startnode = data[0]
	goalnodes = data[1]
	graph = data[2]
	stime = data[3]
	visited = []
	node = (startnode, stime)
	return (recursive_DFS(node, goalnodes, graph, visited))

def recursive_DFS(node, goalnodes, graph, visited):
	#print (node)
	visited.append(node[0])
	if node[0] in goalnodes:
		return node
	else:
		for child in sorted([x[0] for x in graph[node[0]]]):
			if child in visited:
				continue
			child_node = (child, (node[1]+1)%24)
			result = recursive_DFS(child_node, goalnodes, graph, visited)
			if len(result) > 1:
				return result
		return ("None",)


def runUCS(data):
	startnode = data[0]
	goalnodes = data[1]
	graph = data[2]
	stime = data[3]
	node = (stime, startnode)
	frontier = []
	heappush(frontier, node)
	explored = set()
	while True:
		if len(frontier) == 0:
			return ("None", )
		node = heappop(frontier)
		#print (node)
		if node[1] in goalnodes:
			return (node[1], node[0]%24)
		explored.add(node[1])
		for edge in graph[node[1]]:
			if edge[2][node[0]%24] == False:
				continue
			child = (node[0] + edge[1], edge[0])
			if child[1] not in explored and child[1] not in [x[1] for x in frontier]:
				heappush(frontier, child)
			elif child[1] in [x[1] for x in frontier]:
				j = -1
				for i in range(0, len(frontier)):
					if child[1] == frontier[i][1]:
						if child[0] < frontier[i][0]:
							j = i
							break
				if j >= 0:
					frontier[j] = child
					heapify(frontier)











def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt=="-i":
			inputfile = arg
	f2 = open("output.txt", "w")
	f2.close()
	with open(inputfile, "r") as f1:
		tcases = int(f1.readline().rstrip('\n'))
		case = 0
		while case<tcases:
			algo, data = getInput(f1)
			pp = pprint.PrettyPrinter(indent=4)
			#pp.pprint(algo)
			#pp.pprint(data)
			if algo == "BFS":
				result = runBFS(data)
			elif algo == "DFS":
				result = runDFS(data)
			elif algo == "UCS":
				result = runUCS(data)
				#print (result)
			with open("output.txt", "a") as f2:
				f2.write(result[0])
				if len(result) > 1:
					f2.write(" " + str(result[1]))
				f2.write('\n')
			case += 1





if __name__ == "__main__":
   main(sys.argv[1:])