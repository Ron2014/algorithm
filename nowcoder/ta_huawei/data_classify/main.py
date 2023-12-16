from __future__ import print_function # never new line for <print> in python2
import sys
'''
15 123 456 786 453 46 7 5 3 665 453456 745 456 786 453 123
5 6 3 6 3 0
---
30 3 6 0 123 3 453 7 3 9 453456 13 453 14 123 6 7 1 456 2 786 4 46 8 665 9 453456 11 456 12 786

7 6396 4598 8539 6047 2019 11269 7402
3 16 4 26
---
12 4 3 1 4598 3 6047 6 7402 26 1 5 11269

'''
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        str_datas = line.split()

        info_count = int(str_datas[0])
        info_db = []
        for i in xrange(info_count):
            info_db.append(str_datas[i+1])

        line = sys.stdin.readline().strip()
        str_checks = line.split()

        check_count = int(str_checks[0])
        check_datas = []
        for i in xrange(check_count):
            check_datas.append(int(str_checks[i+1]))
        check_datas = map(str, sorted(check_datas))

        # print(info_db)
        # print(check_datas)

        total_count = 0
        output_list = []
        already_checked = set([])
        for i, check in enumerate(check_datas):
            if check in already_checked:
                continue
            already_checked.add(check)

            match_list = []
            match_count = 0
            for j, info in enumerate(info_db):
                if check in info:
                    match_count += 1
                    match_list.append(str(j))
                    match_list.append(info)
                    
            if match_count > 0:
                output_list.append(check)
                output_list.append(str(match_count))
                output_list.extend(match_list)
                total_count += 2 + match_count * 2

        print(total_count,end=' ')
        print(" ".join(output_list),end='\n')

except:
    pass