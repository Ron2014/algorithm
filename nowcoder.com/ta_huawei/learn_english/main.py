import sys
UNITS = ["", "thousand", "million", "billion"]
NUM2ENG = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]
TEN2ENG = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        str_left = line
        i = 0

        result = []
        while str_left:
            unit = UNITS[i]
            str_proc = str_left[-3:]
            str_left = str_left[:-3]
            i += 1
         
            result_proc = []
            
            str_hundred = str_proc[:-2]
            str_under_hundred = str_proc[-2:]

            if str_hundred and str_hundred != '0':
                result_proc.append(NUM2ENG[int(str_hundred)])
                result_proc.append("hundred")
            
            if str_under_hundred and str_under_hundred != '0':
                if result_proc:
                    result_proc.append("and")
                int_under_hundred = int(str_under_hundred)
                if int_under_hundred < 20:
                    result_proc.append(NUM2ENG[int_under_hundred])
                else:
                    result_proc.append(TEN2ENG[int_under_hundred/10])
                    mod = int_under_hundred%10
                    if mod:
                        result_proc.append(NUM2ENG[mod])
            if unit:
                result_proc.append(unit)
            
            result.append(" ".join(result_proc))
            
        print " ".join(result[::-1])
except:
    pass