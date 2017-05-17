# Rope Burning Riddler from fivethirtyeight.com

def explore(situation):

	ropes = situation[0]
	time = situation[1]

	# Find unextinguished ropes and make a list of those 
	# with at least 1 unlit end.
	allextinguished = True
	ropestochoose = []
	for r in range(N):
		if ropes[r][1] == 0 or ropes[r][1] > time:
			allextinguished = False
			if not ropes[r][0] ==2:
				ropestochoose.append(r)
	if allextinguished:
		# No descendent situations, so tally the intervals
		for rope in ropes:
			time = rope[1]
			if not time in times:
				times.append(time)
		# Comment-out the following block to ignore 
		# periods between extinguishings
		for rope1 in ropes:
			for rope2 in ropes:
				time = abs(rope1[1]-rope2[1])
				if not time in times:
					times.append(time)
		return
	# A choice is to (0) do nothing, (1) ignite a first 
	# end if unignited (2) ignite (both first and) 
	# second end if unignited. The choice for a particular 
	# rope R (0 to len(ropestochoose)-1) is (choices//3**R)%3 
	# (think of choices as a base-3 numeral).
	for choices in range(1,3**len(ropestochoose)):
		# We will modify a copy of ropes
		newropes = list(ropes)
		for r in range(len(ropestochoose)):
			rope = newropes[ropestochoose[r]]
			choice = (choices//3**r)%3
			if rope[0] == 0:
				# No ends lit
				if choice == 1:
					rope = [1,time+1]
				elif choice == 2:
					rope = [2,time+.5]
			elif rope[0] == 1:
				# One end already lit
				if choice == 2:
					rope = [2,time+.5*(rope[1]-time)]
			newropes[ropestochoose[r]] = rope
		# This will prevent redundantly exploring equivalent situations
		newropes.sort(reverse=True)	
		# Find time of next extinguishing
		nexttime = min([rope[1] for rope in newropes if rope[1] > time])
		newsituation = [newropes,nexttime]
		if newropes == ropes or newsituation in already_explored:
			continue
		already_explored.append(newsituation)
		explore(newsituation)

# Main program

# Numbers of ropes to do
MinRopes = 1
MaxRopes = 6

for N in range(MinRopes,MaxRopes+1):
	# ropes is a list of pairs. each pair is: [ends-lit 
	# (0, 1, or 2), time (has been or will be) extinguished].
	# We start with extinction time 0 as a dummy value.
	ropes = [[0,0]]*N
	time = 0
	situation = [ropes,time]

	# Keep track of the situations we have already processed
	already_explored = [situation]

	# This is our list of the durations we can measure
	times = []

	# Recursively explore the achievable situations
	explore(situation)

	# Done. Tidy up and finish.
	if 0 in times:
		# 0 is not a duration per problem statement.
		times.remove(0)
	times.sort()
	print(N,"ropes measure",len(times), "intervals")
	# print(times)
