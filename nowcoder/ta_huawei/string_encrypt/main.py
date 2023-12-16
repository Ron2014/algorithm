
import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        encrypt_key = line
        plaint_text = sys.stdin.readline().strip()

        exist_idx = set([])
        new_encrypt_key = []

        for c in encrypt_key:
            if c.isupper():
                ic = ord(c) - ord('A')
            else:
                ic = ord(c) - ord('a')
            if ic in  exist_idx:
                continue
            exist_idx.add(ic)
            new_encrypt_key.append(ic)

        for i in xrange(26):
            if i in exist_idx:
                continue
            new_encrypt_key.append(i)
        
        cipher_text = []
        for i, c in enumerate(plaint_text):
            if c.isalpha():
                if c.isupper():
                    ic = ord(c) - ord('A')
                    nic = new_encrypt_key[ic]
                    nc = chr(ord('A') + nic)
                else:
                    ic = ord(c) - ord('a')
                    nic = new_encrypt_key[ic]
                    nc = chr(ord('a') + nic)
            else:
                nc = c
            cipher_text.append(nc)
        print "".join(cipher_text)
                    




except:
    pass