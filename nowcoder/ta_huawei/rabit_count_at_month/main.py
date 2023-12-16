import sys
'''
f(n): the count of rabits at month n

which means in month n+2, f(n) of rabits have the ability to have baby
so f(n) of <new rabits> will come at month n+2

f(n+2) = f(n+1) + f(n)

it's Fibonacci
'''
try:

    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        month = int(line)

        count_1 = 1
        count_2 = 1
        for i in xrange(2,month):
            count = count_1 + count_2
            count_1 = count_2
            count_2 = count
        print count
except:
    pass