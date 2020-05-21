import sys

MAX_WORD_LEN = 20

words_stack = []
words_count = 0
token = []
token_len = 0

def new_word():
    global words_stack, token, words_count, token_len
    words_stack.append("".join(token))
    words_count += 1
    token = []
    token_len = 0

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        words_stack = []
        words_count = 0
        token = []
        token_len = 0

        for c in line:
            if c.isalpha():
                token.append(c)
                token_len += 1
                if token_len == MAX_WORD_LEN:
                    new_word()
            else:
                if token_len > 0:
                    new_word()

        if token_len > 0:
            new_word()

        newline = []
        for i in xrange(words_count):
            token = words_stack[words_count - 1 - i]
            newline.append(token)
        print " ".join(newline)

except:
    pass