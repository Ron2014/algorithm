from __future__ import print_function # never new line for <print> in python2
import math
prime_list = []

def getResult(num):
    global prime_list
    sqrt = int(math.sqrt(num)) + 1
    for i in xrange(2, sqrt):
        if num % i == 0:
            print(i,end=' ')
            return getResult(num / i)
    print(num,end=' \n') # space after the last num!(make clear the question)

try:
    while True:
        prime_list = []
        line = input()
        if line == '':
            break
        getResult(line)
except:
    pass