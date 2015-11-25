
# This is the main file implementing the backword-chaining algo
# for HW-3 of CSC1 561

import re
import sys
import getopt
import pprint


class KB():

	def __init__(self):
		self.clauses = {}

	def tell(self, sentence):
		clause = parseRule(sentence)
		if clause[0][0:2] in self.clauses:
			self.clauses[clause[0][0:2]].append(clause)
		else:
			self.clauses[clause[0][0:2]] = [clause]


def parseRule(s):
	p1 = re.compile(r"(.+)=>(.+)")
	m = p1.search(s)
	if m:
		rhs = parseLiteral(m.group(2).lstrip())
		lhs_lit = m.group(1).split('^')
		lhs = []
		for lit in lhs_lit:
			lhs.append(parseLiteral(lit.strip()))
		return ((rhs, lhs))
	else:
		return ((parseLiteral(s.strip()), []))


def parseLiteral(s):
	q = re.compile(r"(~?\w+)\((.+)\)")
	m = q.match(s)
	if m:
		arg = m.group(2).split(',')
		argtup = []
		for a in arg:
			if a[0].isupper():
				argtup.append((a, 'c'))
			else:
				argtup.append((a, 'v'))
		if m.group(1)[0] == '~':
			return (m.group(1)[1:], False, argtup)
		else:
			return (m.group(1), True, argtup)

	else:
		print("Error parsing literal")
		return ("", True, [])


def getInput(inputfile):
	query = []
	kb = KB()
	with open(inputfile, "r") as f1:
		qcount = int(f1.readline())
		qno = 0
		while qno < qcount:
			line = f1.readline().rstrip('\n')
			query.append(parseLiteral(line))
			qno += 1
		rcount = int(f1.readline())
		rno = 0
		while rno < rcount:
			line = f1.readline().rstrip('\n')
			kb.tell(line)
			rno += 1
	return (query, kb)


def unify_test():
	with open("unif_test.txt", "r") as f1:
		a = parseLiteral(f1.readline().strip())
		b = parseLiteral(f1.readline().strip())
		q = unify(a[2], b[2], {"meta_fail": False})
		if q["meta_fail"]:
			print("failed to unify")
		pprint.pprint(q)


def unify(x, y, theta):
	# pprint.pprint(x)
	# pprint.pprint(y)
	# pprint.pprint(theta)
	# print("-------------")
	if theta["meta_fail"]:
		return {"meta_fail": True}
	elif x == y:
		return theta
	elif len(x) == 1 and x[0][1] == 'v' and len(y) == 1:
		return unify_var(x[0], y[0], theta)
	elif len(y) == 1 and y[0][1] == 'v' and len(x) == 1:
		return unify_var(y[0], x[0], theta)
	elif len(x) > 1 and len(y) > 1:
		return unify(x[1:], y[1:], unify(x[:1], y[:1], theta))
	else:
		return {"meta_fail": True}


def unify_var(var, x, theta):
	if var in theta:
		return unify([theta[var]], [x], theta)
	elif x in theta:
		return unify([var], [theta[x]], theta)
	else:
		theta[var] = x
		return theta


def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt == "-i":
			inputfile = arg
	f2 = open("output.txt", "w")
	f2.close()
	query, kb = getInput(inputfile)
	# pprint.pprint(query)

if __name__ == "__main__":
	# main(sys.argv[1:])
	unify_test()
