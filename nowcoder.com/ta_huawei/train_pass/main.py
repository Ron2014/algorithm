import sys

results = set([])

def getRecord(trains, input_stack, output_list):
    # print(trains)
    # print(input_stack)
    # print(output_list)

    global results
    if not trains and not input_stack:
        key = tuple(output_list)
        results.add(key)
        return

    if trains:
        new_input = list(input_stack)
        new_input.append(trains[0])
        getRecord(trains[1:], new_input, output_list)
        
    if input_stack:
        new_output = list(output_list)
        new_output.append(input_stack[-1])
        getRecord(trains, input_stack[:-1], new_output)
    

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    results = set([])
    lines = line.split()
    count = int(lines[0])
    if len(lines) > 1:
        trains = map(int, lines[1:])
    else:
        trains = map(int, sys.stdin.readline().strip().split())
    
    # print(trains)
    input_stack = []
    output_list = []
    getRecord(trains, input_stack, output_list)

    result_list = sorted(list(results))
    for train in result_list:
        print " ".join(map(str, train))