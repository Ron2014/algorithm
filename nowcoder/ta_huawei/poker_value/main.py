import sys

T_SINGLE = 1
T_COUPLE = 2
T_TRIPLE = 3
T_SEQUENCE = 4
T_BOOM = 5
T_KINGS = 6

CARDS_VALUE = {
    '3':1,
    '4':2,
    '5':3,
    '6':4,
    '7':5,
    '8':6,
    '9':7,
   '10':8,
    'J':9,
    'Q':10,
    'K':11,
    'A':12,
    '2':13,
'joker':14,
'JOKER':15,
}

def getType(cards):
    if not cards:
        return None
    
    for c in cards:
        if c not in CARDS_VALUE:
            return None

    l = len(cards)
    if l==1:
        # single
        return T_SINGLE
    else:
        if l==2 and "joker" in cards and "JOKER" in cards:
            return T_KINGS

        allSame = True
        firstCard = cards[0]
        for c in cards[1:]:
            if c!=firstCard:
                allSame = False
                break

        if allSame:
            if l==2:
                return T_COUPLE
            elif l==3:
                return T_TRIPLE
            elif l==4:
                return T_BOOM
            else:
                return None

        # sequence?
        
        if l<5:
            return None
        cards = sorted(cards, key=lambda x: CARDS_VALUE.get(x,0))
        for i in xrange(1,l):
            v0 = CARDS_VALUE.get(cards[i-1], 0)
            v1 = CARDS_VALUE.get(cards[i], 0)
            if v1-v0 != 1:
                return None
        return T_SEQUENCE
    
    return None

def biggerBoom(cards0, cards1, type1):
    if type1 == T_BOOM:
        count0 = len(cards0)
        count1 = len(cards1)

        if count0 < count1:
            return 1
        elif count0 > count1:
            return 0
        
        v0 = CARDS_VALUE.get(cards0[0], 0)
        v1 = CARDS_VALUE.get(cards1[0], 0)
        if v0 < v1:
            return 1
        elif v0 > v1:
            return 0
        return None
    return 0

def getBigger(cards0, cards1):
    type0 = getType(cards0)
    type1 = getType(cards1)

    if not type0 or not type1:
        return None
    
    if type0==T_KINGS:
        return 0
    if type1==T_KINGS:
        return 1
    
    if type0==T_BOOM:
        ret = biggerBoom(cards0, cards1, type1)
        if ret == 0:
            return 0
        elif ret == 1:
            return 1
    if type1==T_BOOM:
        ret = biggerBoom(cards1, cards0, type0)
        if ret == 0:
            return 1
        elif ret == 1:
            return 0
    
    if type0!=type1:
        return None

    v0 = CARDS_VALUE.get(cards0[0], 0)
    v1 = CARDS_VALUE.get(cards1[0], 0)
    # print(cards0, cards1)
    # print(v0, v1)
    if v0 < v1:
        return 1
    elif v0 > v1:
        return 0

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    cards = line.split('-')
    # print(cards)
    bigger = getBigger(cards[0].split(), cards[1].split())
    if bigger is None:
        print("ERROR")
    else:
        print(line.split('-')[bigger])