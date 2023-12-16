import sys
UNITS0 = ["角", "分"]
UNITS1 = ["", "拾", "佰", "仟"]
UNITS2 = ["", "万", "亿"]
NUM2WORD = ["零", "壹", "贰","叁","肆","伍","陆","柒","捌","玖",]

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        l = len(line)
        dot = line.find('.')
        decimal = []

        if dot >= 0:
            d = line[dot+1:]
            if int(d):
                if(d[1]=='0'):
                    d = d[:1]
                l = min(len(UNITS0), len(d))
                for i in range(l):
                    if (int(d[i])):
                        decimal.append(NUM2WORD[int(d[i])])
                        decimal.append(UNITS0[i])
            # print(decimal)
            line = line[:dot]

        str_left = line
        i = 0
        result = []
        while str_left:
            unit = UNITS2[i]
            str_proc = str_left[-4:]
            str_left = str_left[:-4]
            i += 1
            
            # sequence 0
            l = len(str_proc)
            result_proc = []
            zero_before = False
            num_before = False
            for j in range(l):
                if str_proc[l-j-1] == '0':
                    if zero_before:
                        continue
                    if num_before:
                        result_proc.append(NUM2WORD[int(str_proc[l-j-1])])
                        zero_before = True
                else:
                    result_proc.append(UNITS1[j])
                    if str_proc[l-j-1] =='1' and j==1:
                        pass
                    else:
                        result_proc.append(NUM2WORD[int(str_proc[l-j-1])])
                    zero_before = False
                    num_before = True

            result_proc = result_proc[::-1]
            if unit:
                result_proc.append(unit)
            result.append("".join(result_proc))
        
        result = "".join(result[::-1])
        if result:
            result = ["人民币", result, "元"]
        else:
            result = ["人民币"]

        if decimal:
            result.extend(decimal)
        else:
            if len(result) > 1:
                result.append("整")
            else:
                result.append("零元")
        print("".join(result))
except:
    pass