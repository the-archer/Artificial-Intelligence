import sys




def makeMove(player, p2, p1, blen, m2, m1, i):
	val = 0
	stones = 0
	curside = player
	curbox = i
	if player == 1:
		stones = p1[i]
	else:
		stones = p2[i]
	
	while stones > 0:
		stones -= 1
		if curside == 1:
			curbox += 1
			if curbox > blen:
				curbox = blen - 1
				curside = 2
		else:
			curbox -= 1
			if curbox < -1:
				curbox = 0
				curside = 1
		if curbox == blen:
			if player == 1:
				m1 += 1
				if stones == 0:
					board, val = runGreedy(player, p2, p1, blen, m2, m1)
					return [board, val]
				continue
			else:
				curbox = blen - 1

		elif curbox == -1:
			if player == 1:
				curbox = 0
			else:
				m2 += 1
				if stones == 0:
					board, val = runGreedy(player, p2, p1, blen, m2, m1)
					return [board, val]
				continue

		if player == 1:
			p1[curbox] += 1
			if stones == 0:
				if p1[curbox] = 1:
					m1 += p2[curbox]
					m1 += 1
					p1[curbox] = 0
		else:
			p2[curbox] += 1
			if stones == 0:
				if p2[curbox] == 1:
					m2 += p1[curbox]
					m2 += 1
					p2[curbox] = 0 

	val = eval(m1, m2)
	board = [p2, p1, m2, m1]
	return [val, board]

		


def eval(m1, m2):
	return m1-m2


def runGreedy(player, p2, p1, blen, m2, m1):
	pp = []
	bestval = 0
	nextstate = []
	if player==1:
		pp = p1
		bestval = -float("inf")
	else:
		pp = p2
		bestval = float("inf")
	for i in range(0, blen):
		if pp[i] != 0:
			board, val = makeMove(player, p2, p1, blen, m2, m1, i)
			if player==1 and val > bestval:
				bestval = val
				nextstate = board
			elif player==2 and val < bestval:
				bestval = val
				nextstate = board


def getInput(inputfile):
	with open(inputfile, "r") as f1:
		algo = int(f1.readline().rstrip('\n'))
		player = int(f1.readline().rstrip('\n'))
		cutdepth = int(f1.readline().rstrip('\n'))
		p2 = [int(x) for x in f1.readline().rstrip('\n').split()]
		p1 = [int(x) for x in f1.readline().rstrip('\n').split()]
		blen = len(p1)
		m2 = int(f1.readline().rstrip('\n'))
		m1 = int(f1.readline().rstrip('\n'))
		return [algo, player, cutdepth, p2, p1, blen, m2, m1]


def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt=="-i":
			inputfile = arg
	algo, player, cutdepth, p2, p1, blen, m2, m1 = getInput(inputfile)
	if algo == 1:
		runGreedy(player, p2, p1, blen, m2, m1)




if __name__ == "__main__":
   main(sys.argv[1:])