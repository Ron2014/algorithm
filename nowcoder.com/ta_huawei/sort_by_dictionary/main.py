import sys
while True:
    input_list = []

    try:
        count = input()
    except:
        break

    for i in xrange(count):
        word = sys.stdin.readline().strip()
        input_list.append(word)
        
    for word in sorted(input_list):
        print(word)
