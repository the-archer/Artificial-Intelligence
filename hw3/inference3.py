
# This is the main file implementing the backword-chaining algo
# for HW-3 of CSC1 561

import re
import sys
import getopt


class KB():

	def __init__(self):
		self.clauses = {}

	def tell(self, sentence):
		return




def parseQuery(s):
	q = re.compile(r"(~?\w+)\((.+)\)")
	m = q.match(s)
	if m:
		arg = m.group(2).split(',')
		argtup = []
		for a in arg:
			argtup.append((a, 'c'))
		if m.group(1)[0] == '~':
			return (m.group(1)[1:], False, argtup)
		else:
			return (m.group(1), True, argtup)

	else:
		print("Error parsing query")
		return ("", True, [])


def getInput(inputfile):
	query = []
	kb = KB()
	with open(inputfile, "r") as f1:
		qcount = int(f1.readline())
		qno = 0
		while qno < qcount:
			line = f1.readline().rstrip('\n')
			query.append(parseQuery(line))
			qno += 1
		rcount = int(f1.readline())
		rno = 0
		while rno < rcount:
			line = f1.readline().rstrip('\n')
			kb.tell(line)
			rno += 1


def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt == "-i":
			inputfile = arg
	f2 = open("output.txt", "w")
	f2.close()
	query, kb = getInput(inputfile)


if __name__ == "__main__":
	main(sys.argv[1:])
