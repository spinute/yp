import commands
import os
import string

def from_ms_format_to_s(st):
    m_str = ""
    s_str = ""
    find_f = False
    for s in st:
        if find_f == True :
            if s != 's' :
                s_str = s_str + s
            continue

        if s != 'm' :
            m_str = m_str + s
        else :
            find_f = True
    return str( float(m_str) * 60.0 + float(s_str) )


        

def output_execute_time(log_file_name, write_file_name):
    f = open("../results/" +  write_file_name, 'w')
    results = commands.getoutput("grep ',' -v ../" + log_file_name + " | grep -v STAT | grep -v sys | sed '/^\s*$/d'")
    results = results.split('\n')
    for result in results:
        if result.find("real") >= 0:
            result = str(result).replace('real', '')
            result = result.strip()
            f.write(from_ms_format_to_s(result))
            print( result + " " + from_ms_format_to_s(result))
            f.write("\n")
    f.close() 

def test_f_limit(log_file_name, ans_file_name, problems_nums):
    ans_hash = {}
    ans_array = []
    for line in open(ans_file_name, 'r'):
        array = line.split()
        if len(array) == 0:
            break
        ans_hash[array[0]] = array[1]
        ans_array.append(array[1])

    results = commands.getoutput("grep ',' -v ../" + log_file_name + " | grep -v STAT | grep -v sys | sed '/^\s*$/d'")
    results = results.split('\n')
    # for ans in ans_array:
    #     print(ans)
    tmp_f_limit = ""
    log_limits = []
    log_times = []
    for result in results:
        if result.find("f_limit=") >= 0:
            tmp_f_limit = result.replace('f_limit=', '')
        elif result.find("real") >= 0:
            log_limits.append(tmp_f_limit)
            log_times.append(result.replace('real', ''))


    #check
    true_counts = 0
    false_counts = 0

    for i in xrange(0,problems_nums):
        if log_limits[i] == ans_array[i]:
            true_counts += 1
            print("correct " + str(i) + "th problem. true ans is " + ans_array[i] + " : solver's ans is " + log_limits[i])
        else:
            print("wrong " + str(i) + "th problem. true ans is " + ans_array[i] + " : solver's ans is " + log_limits[i])
            false_counts += 1

    print "--------------------------------"
    print (log_file_name)
    print str(problems_nums) + " test cases"
    print "correct cases are " + str(true_counts)
    print "wrong cases are " + str(false_counts)
    print "--------------------------------"




# 15puzzle
test_f_limit("log_pbida4", "15puzzle_answers.txt", 100)
test_f_limit("log_pbida4_global", "15puzzle_answers.txt", 100)

test_f_limit("log_pbida4_find_all", "15puzzle_answers.txt", 100)
test_f_limit("log_pbida4_global_find_all", "15puzzle_answers.txt", 100)


output_execute_time("log_pbida4", "15puzzle_bpida_korf100.txt")
output_execute_time("log_pbida4_global", "15puzzle_bpida_global_korf100.txt")


output_execute_time("log_pbida4_find_all", "15puzzle_bpida_findall_korf100.txt")
output_execute_time("log_pbida4_global_find_all", "15puzzle_bpida_global_findall_korf100.txt")


# 24puzzle
test_f_limit("log_pbida5_find_all", "24puzzle_yama_answers.txt", 50)
test_f_limit("log_pbida5_global_find_all", "24puzzle_yama_answers.txt", 50)

test_f_limit("log_pbida5_pdb_find_all", "24puzzle_yama_answers.txt", 50)

test_f_limit("log_pbida5_pdb_global_find_all", "24puzzle_yama_answers.txt", 50)

test_f_limit("log_c5_pdb_find_all", "24puzzle_yama_answers.txt", 50)



output_execute_time("log_pbida5_find_all", "24puzzle_bpida_findall_yama.txt")
output_execute_time("log_pbida5_global_find_all", "24puzzle_bpida_global_findall_yama.txt")

output_execute_time("log_pbida5_pdb_global_find_all", "24puzzle_bpida_pdb_global_findall_yama.txt")

output_execute_time("log_pbida5_pdb_find_all", "24puzzle_bpida_pdb_findall_yama.txt")
output_execute_time("log_c5_pdb_find_all", "24puzzle_c5_pdb_findall_yama.txt")


# test_f_limit("log_pbida4", "15puzzle_answers.txt", 100)
# test_f_limit("log_pbida5_find_all", "15puzzle_answers.txt", 100)
# test_f_limit("log_pbida5_find_all", "15puzzle_answers.txt", 100)
