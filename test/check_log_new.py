import commands
import os
import string

bench_marks_4 = ["korf100"]
bench_marks_5 = ["yama24_50_hard_new"]
bench_marks_5_korf = ["korf-24-easy10"] 
solver_4 = ["bpida4", "bpida4_global", "c4", "bpida4_fa", "bpida4_global_fa", "c4_fa"]
solver_5 = ["bpida5", "bpida5_global", "bpida5_pdb", "bpida5_pdb_global", "c5", "c5_pdb", "bpida5_fa", "bpida5_global_fa", "bpida5_pdb_fa", "bpida5_pdb_global_fa", "c5_fa", "c5_pdb_fa"]
solver_5_pdb = ["bpida5_pdb", "bpida5_pdb_global", "c5_pdb",  "bpida5_pdb_fa", "bpida5_pdb_global_fa", "c5_pdb_fa"]
solver_5_sh = ["bpida5_global_sh_fa_4312", "bpida5_global_sh_fa_8720", "bpida5_global_sh_fa_13128", "bpida5_global_sh_fa_17536", "bpida5_global_sh_fa_35168"]

ans_file_hash = {}	
ans_file_hash["korf100"] = "15puzzle_answers.txt"
ans_file_hash["yama24_50_hard_new"] = "24puzzle_yama_answers.txt"
ans_file_hash["korf-24-easy10"] = "24puzzle_korf_answers10.txt"

def output_results(log_file_name):
	depth_results       = commands.getoutput("grep -r 'solution_depth' ../log/" + log_file_name)
	# print("grep -r 'solution_depth' ../log/" + log_file_name)
	time_results        = commands.getoutput("grep -r 'Timer:search' ../log/" + log_file_name)
	total_nodes_results = commands.getoutput("grep -r 'total_nodes_evaluated' ../log/" + log_file_name)

	depth_results = depth_results.split('\n')
	time_results = time_results.split('\n')
	total_nodes_results = total_nodes_results.split('\n')

	assert len(depth_results) == len(time_results)
	assert len(time_results) == len(total_nodes_results)

	problem_nums = len(depth_results)

	f = open("../results/" +  log_file_name, 'w')

	for i in xrange(0, problem_nums):
		d = depth_results[i].replace('[Stat:solution_depth]=', '')
		t = time_results[i].replace('[Timer:search] ', '')
		n = total_nodes_results[i].replace('[Stat:total_nodes_evaluated]', '')
		f.write(d + " " + t + " " + n + " " + str(float(n) / float(t))  + '\n')
		# print(d + " " + t + " " + n)

	f.close()

def test_find_error(log_file_name):
	errors = commands.getoutput("grep -r 'Error:' ../log/" + log_file_name)
	flag = len(errors) == 0
	errors = errors.split('\n')
	for e in errors:
		print e

	return flag


def test_f_limit(log_file_name, ans_file_name):
	depth_results  = commands.getoutput("grep -r 'solution_depth' ../log/" + log_file_name)
	depth_results = depth_results.split('\n')
	ans_hash = {}
	ans_array = []
	for line in open(ans_file_name, 'r'):
		array = line.split()
		if len(array) == 0:
			break
		ans_hash[array[0]] = array[1]
		ans_array.append(array[1])

	valid_f = True

	if len(ans_array) != len(depth_results) :
		valid_f = False

	for x in xrange(0,len(depth_results)):
		depth = depth_results[x].replace('[Stat:solution_depth]=', '')
		if ans_array[x] != depth :
			print(str(x) + "th true: " + ans_array[x] + "false: " + depth)
			valid_f = False
		# assert ans_array[x] == depth

	return valid_f

def exec_test(log_file_name, ans_file_name):
	if test_f_limit(log_file_name, ans_file_name) & test_find_error(log_file_name):
		print(log_file_name + " : OK")
		return
	print(log_file_name + " : failed")


for b in bench_marks_4:
	for solver in solver_4:
		log_f_name = b + "_" + solver
		output_results(log_f_name)
		exec_test(log_f_name, ans_file_hash[b])

for b in bench_marks_5:
	for solver in solver_5:
		log_f_name = b + "_" + solver
		output_results(log_f_name)
		exec_test(log_f_name, ans_file_hash[b])

for b in bench_marks_5_korf:
	for solver in solver_5_pdb:
		log_f_name = b + "_" + solver
		output_results(log_f_name)
		exec_test(log_f_name, ans_file_hash[b])

for b in bench_marks_5:
	for solver in solver_5_sh:
		log_f_name = b + "_" + solver
		output_results(log_f_name)
		exec_test(log_f_name, ans_file_hash[b])

