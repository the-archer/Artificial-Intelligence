
# This is the main file implementing the backword-chaining algo
# for HW-3 of CSC1 561

import re
import sys
import getopt
import pprint
from copy import deepcopy

var_count = 0


class KB():

	def __init__(self):
		self.clauses = {}

	def tell(self, sentence):
		clause = parseRule(sentence)
		# standardize_test(clause)
		if clause[0][0:2] in self.clauses:
			self.clauses[clause[0][0:2]].append(clause)
		else:
			self.clauses[clause[0][0:2]] = [clause]

	def fetch_rules_for_goal(self, goal):
		# print ("goal" + str(goal))
		rules = []
		if goal[0:2] in self.clauses:
			# print ("here")
			for rule in self.clauses[goal[0:2]]:
				# print ("Rule" + str(rule))
				# yield rule
				rules.append(rule)
				# return rule
		return rules

	def printKB(self):
		pprint.pprint(self.clauses)


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
	thetan = deepcopy(theta)
	if thetan["meta_fail"]:
		return {"meta_fail": True}
	elif x == y:
		# nt ("test")
		return thetan
	elif len(x) == 1 and x[0][1] == 'v' and len(y) == 1:
		return unify_var(x[0], y[0], thetan)
	elif len(y) == 1 and y[0][1] == 'v' and len(x) == 1:
		return unify_var(y[0], x[0], thetan)
	elif len(x) > 1 and len(y) > 1:
		return unify(x[1:], y[1:], unify(x[:1], y[:1], thetan))
	else:
		return {"meta_fail": True}


def unify_var(var, x, thetan):
	theta = deepcopy(thetan)
	# pprint.pprint(var)
	# pprint.pprint(x)
	# pprint.pprint(theta)
	if var in theta:
		return unify([theta[var]], [x], theta)
	elif x in theta:
		return unify([var], [theta[x]], theta)
	else:
		theta[var] = x
		return theta


def standardize_test(rule):
	rule = standardize_variables(rule)
	# pprint.pprint(rule2)


def standardize_variables(rule):
	# print(rule)
	global var_count
	var_count += 1
	for i, arg in enumerate(rule[0][2]):
		if arg[1] == 'v':
			cur = rule[0][2][i][0][0]
			rule[0][2][i] = (cur + str(var_count), 'v')
	for j in range(len(rule[1])):
		for i, arg in enumerate(rule[1][j][2]):
			if arg[1] == 'v':
				cur = rule[1][j][2][i][0][0]
				rule[1][j][2][i] = (cur + str(var_count), 'v')
	return rule


def fol_bc_or(kb, goal, theta, parentgoals, i):
	# print("goal")
	# pprint.pprint(goal)
	# for j in range(0, i):
		# fsim.write("\t")
	# fsim.write(goal)
	# pprint.pprint(goal, fsim)
	# fsim.flush()
	# pprint.pprint(theta)
	# print("-----------")
	# print (goal)
	thetan = deepcopy(theta)
	parentgoalsn = deepcopy(parentgoals)
	# print("parentgoals")
	# pprint.pprint(parentgoalsn)
	# input()
	for arg in goal[2]:
		if arg[1] == 'v':
			break
	else:  # no-break
		if goal in parentgoalsn:
			thetan["meta_fail"] = True
			# print ("loop break")
			yield thetan
	parentgoalsn.append(goal)
	rules = kb.fetch_rules_for_goal(goal)
	for rule in rules:
		# print (len(rules))
		rhs, lhs = standardize_variables(rule)
		# print("goal:" + str(goal))
		# print(rhs)
		# print(lhs)
		# print("theta: "+ str(thetan))
		for theta1 in fol_bc_and(kb, lhs, unify(rhs[2], goal[2], thetan), parentgoalsn, i):
			# print("theta1: " + str(theta))
			yield theta1


def fol_bc_and(kb, goals, theta, parentgoals, i):
	# print("goals")
	# pprint.pprint(goals)
	# print(goals)
	# print(theta)
	# input()
	thetan = deepcopy(theta)
	parentgoalsn = deepcopy(parentgoals)
	if thetan["meta_fail"]:
		# print("fail")
		return
	elif len(goals) == 0:
		# print("theta")
		# pprint.pprint(thetan)
		yield thetan
	else:
		first = deepcopy(goals[0])
		rest = deepcopy(goals[1:])
		for theta1 in fol_bc_or(kb, substitute(thetan, first), thetan, parentgoalsn, i+1):
			for theta2 in fol_bc_and(kb, rest, theta1, parentgoalsn, i):
				# print("theta2: " + str(theta2) )
				yield theta2


def substitute(theta, clause):
	# print(theta)
	# print(clause)
	args = []
	for arg in clause[2]:
		if arg[1] == 'v' and arg in theta:
			args.append(theta[arg])
		else:
			args.append(arg)
	# print ("args"+ str(args))
	return (clause[0], clause[1], args)


def fol_bc_ask(kb, query):
	return fol_bc_or(kb, query, {"meta_fail": False}, [], 0)


def main(argv):
	optlist, args = getopt.getopt(argv, 'i:')
	for opt, arg in optlist:
		if opt == "-i":
			inputfile = arg
	f2 = open("output.txt", "w")
	query, kb = getInput(inputfile)
	# kb.printKB()
	# print ("----------")
	for q in query:
		flag = False
		for res in fol_bc_ask(kb, q):
		#res = list(fol_bc_ask(kb, q))
			f2.write("TRUE\n")
			f2.flush()
			flag = True
			break
		if not flag:
			f2.write("FALSE\n")
			f2.flush()

if __name__ == "__main__":
	main(sys.argv[1:])
	# unify_test()
