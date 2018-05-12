import commands
import os


# class TestLog():
#     ans_hash = {}
#     ans_array = []
    
#     def __init__(self, arg):
#         super(TestLog, self).__init__()
#         self.arg = arg

#     def set_answers


# TestLog tl = TestLog('15puzzle_answers.txt')



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
    print str(problems_nums) + " test cases"
    print "correct cases are " + str(true_counts)
    print "wrong cases are " + str(false_counts)
    print "--------------------------------"

    
test_f_limit("log_pbida4", "15puzzle_answers.txt", 100)
test_f_limit("log_pbida4_find_all", "15puzzle_answers.txt", 100)
# test_f_limit("log_pbida4", "15puzzle_answers.txt", 100)
# test_f_limit("log_pbida5_find_all", "15puzzle_answers.txt", 100)
# test_f_limit("log_pbida5_find_all", "15puzzle_answers.txt", 100)
