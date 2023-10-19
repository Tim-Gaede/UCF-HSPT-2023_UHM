# Author : Juan Moscoso


'''
fail[i] = probability of failing on the ith task
if we fail on the ith task, this means we succeeded on all tasks before it

time[i] = amount of time it takes to do all tasks up to the ith task including the ith task
success = probability that we succeed all tasks

E(x) = the amount of time it takes him to beat UHC
E(x) = fail[1] * (time[1] + E(x)) + fail[2] * (time[2] + E(x)) + ... + fail[n] * (time[n] + E(x)) + (success * times[n])

simplifying we get

E(x) = fail[1] * time[1] + fail[1] * E(x) + fail[2] * time[2] + fail[2] * E(x) + ... + fail[n] * time[n] + fail[n] * E(x) + (success * times[n])

now solving for E(x), we get

E(x) - fail[1] * E(x) - fail[2] * E(x) - ... - fail[n] * E(x) = fail[1] * time[1] + fail[2] * time[2] + ... + fail[n] * time[n] + (success * times[n])
(1 - fail[1] - fail[2] - ... - fail[n])(E(x)) = fail[1] * time[1] + fail[2] * time[2] + ... + fail[n] * time[n] + (success * times[n])

E(x) = fail[1] * time[1] + fail[2] * time[2] + ... + fail[n] * time[n] + (success * times[n])
	   --------------------------------------------------------------------------------------
	   				(1 - fail[1] - fail[2] - ... - fail[n])
 
'''
from itertools import accumulate

# read in the input
n = int(input())
probabilities = list(map(float, input().split()))
task_times = list(map(int, input().split()))
success = 1
fail = []
# accumulate allows us to make a prefix sum of our times for each task
time = list(accumulate(task_times))
for probability in probabilities:
	# (1 - probability) is the probability that we fail at this task
	# success variable is the probability that we passed all other tasks before us
	fail.append(success * (1 - probability))
	success *= probability

# since we have now calculated fail and time
# we can now calculate our denominator and numerator
numerator = (success * time[n - 1])
denominator = 1
for i in range(n):
	numerator += (fail[i] * time[i])
	denominator -= fail[i]

expected_time = numerator / denominator
print(expected_time)
