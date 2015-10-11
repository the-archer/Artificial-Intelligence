import sys
import random
import string




def gen_random_graph(nodecount, goalnode_prob, edge_prob, block_prob):
	graph = dict()
	goalnodes = set()
	midnodes = set()
	chosen_strings = set()
	allnodes = []
	startnode = ""
	flag = False
	edges = 0
	for node in range(0, nodecount):
		s = ""
		for i in range(0, 4):
			s += random.choice(string.ascii_uppercase)
		while s in chosen_strings:
			s += random.choice(string.ascii_uppercase)
		chosen_strings.add(s)
		graph[s] = []
		allnodes.append(s)
		if not flag:
			startnode = s
			flag = True
			continue
		if random.random() < goalnode_prob:
			goalnodes.add(s)
		else:
			midnodes.add(s)

	for i in range(0, len(allnodes)):
		for j in range(0, len(allnodes)):
			if i==j:
				continue
			start = allnodes[i]
			end = allnodes[j]
			if random.random() > edge_prob:
				continue
			cost = int(random.random()*40)
			status = ""
			st = -1
			en = -1
			offp = 0
			cur = True
			for x in range(0, 24):
				if random.random()<block_prob:
					#status[x] = False
					if cur:
						cur = False
						s = x
				else:
					if not cur:
						cur = True
						status += " " + str(s)+"-"+str(x)
						offp += 1
			graph[start].append([end, cost, str(offp) + status])
			edges += 1

	return (startnode, goalnodes, midnodes, edges, graph, int(random.random()*23))






if __name__ == "__main__":
	f1 = open("auto_testcases.txt", "w")
	testcases = 10
	f1.write(str(testcases*3)+"\n")
	for i in range(0, testcases):
		startnode, goalnodes, midnodes, edges, graph, stime = gen_random_graph(random.choice([100, 500]), random.choice([0.01, 0.05, 0.1, 0.2]), random.choice([0.05, 0.1, 0.2, 0.4, 0.5, 0.8]), random.choice([0.001, 0.01, 0.2, 0.5, 0.76]))
		for algo in ["BFS", "DFS", "UCS"]:
			f1.write(algo + '\n')
			f1.write(startnode+'\n')
			for node in goalnodes:
				f1.write(node+' ')
			f1.write('\n')
			for node in midnodes:
				f1.write(node+ ' ')
			f1.write('\n')
			f1.write(str(edges) + '\n')
			for s in graph:
				for e in graph[s]:
					f1.write(s + " " + e[0] + " " + str(e[1]) + " " + e[2] + '\n')
			f1.write(str(stime) + "\n")
			f1.write("\n")
			print ("Done")
	f1.close()
 	






