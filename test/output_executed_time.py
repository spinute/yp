import glob
import commands
import os
import string

file_list_fa = glob.glob('../results/*fa*')

print("| solver (find all) | executed_times | expand_nodes | expand_nodes / sec| \n|:---:|:---:|:---:|:---:|")

for file in file_list_fa:
	f = open(file)
	lines = f.readlines()
	f.close()

	executed_times = 0.0
	expand_nodes = 0
	per_sec = 0.0
	for line in lines:
		arr = line.split(' ')
		executed_times += float(arr[1])
		expand_nodes += int(arr[2])
		per_sec += float(arr[3])
	print("|" +file.replace("../results/", "") + "|" + str(executed_times) + "|" + str(expand_nodes) + "|" + str(per_sec) + "|" )

print("")


file_list = glob.glob('../results/*')
print("| solver | executed_times | expand_nodes | expand_nodes / sec| \n|:---:|:---:|:---:|:---:|")

for file in file_list:
	f = open(file)
	lines = f.readlines()
	f.close()
	if file.find("fa") != -1:
		continue

	executed_times = 0.0
	expand_nodes = 0
	per_sec = 0.0
	for line in lines:
		arr = line.split(' ')
		executed_times += float(arr[1])
		expand_nodes += int(arr[2])
		per_sec += float(arr[3])
	print("|" +file.replace("../results/", "") + "|" + str(executed_times) + "|" + str(expand_nodes) + "|" + str(per_sec / float(len(lines)) ) + "|" )