
while True:
    input_list = []
    input_set = set([])

    try:
        count = input()
    except:
        break

    for i in xrange(count):
        n = input()
        if n not in input_set:
            input_set.add(n)
            input_list.append(n)

    for n in sorted(input_list):
        print(n)
