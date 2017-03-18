from random import random 

def IsConvex(quad):
	answer = True
	for i in range(4):
		x1,y1 = quad[i-2]
		x2,y2 = quad[i-1]
		x3,y3 = quad[i]
		a,b = x1-x2,y1-y2
		c,d = x3-x2,y3-y2
		if a*d < b*c:
			answer = False
	return answer

reps = 1000000
accum = 0
for rep in range(reps):
	quad = []
	for i in range(4):
		quad.append([random(),random()])
	if IsConvex(quad):
		accum += 1

print(accum/reps)


