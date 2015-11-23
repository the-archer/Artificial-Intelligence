import re
pattern = re.compile(r"(.+)=>(.+)")
p2 = re.compile(r"(~?\w+)\((.+)\)")
with open("input_reg.txt", "r") as f1:
	for line in f1:
		# print(line)
		a = pattern.match(line)
		if a:
			print(line.rstrip('\n'))
			print(a.group(2))
			sec = a.group(2)
			b = p2.search(sec)
			if b:
				print(b.group(1))
				print(b.group(2).split(','))
