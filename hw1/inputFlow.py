import sys, getopt
import pprint


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








def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt=="-i":
			inputfile = arg

	with open(inputfile, "r") as f1:
		tcases = int(f1.readline().rstrip('\n'))
		case = 0
		while case<tcases:
			algo, data = getInput(f1)
			pp = pprint.PrettyPrinter(indent=4)
			pp.pprint(algo)
			
			pp.pprint(data)
			case += 1













if __name__ == "__main__":
   main(sys.argv[1:])