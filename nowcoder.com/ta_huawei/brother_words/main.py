'''
473 bb daccb caddd bddc c baa adb ad abbcb cdaa abab a abcc ddcbd cadcc cdacd aaa a b acccd bbb dacc cc acbdd bcbb ba bacaa adda acd aaad d ab acac bc dabab abcd aacba aba daa bb ad cddab a bbaa aacad cdac acbcc cada bacd adcad cdadc bcbcc aa b acd cbaac ddcd ccb dac a dac adbcb bcda dda a ab ca dd d abd a dbb ccabd bdddd abd adc aaa baccb ccdcd a da c cadc dcdbd d aa bb a cac c ad adb ca cdcc cadd dddca d cba cb caab caa dd cd bca abc cdaa cdb bad dad bda d ddbc dab baaa adaac b a dbccd bd b bdad cdacd baa ac ddcad d bb acc aa cd cbdbb bbbcb a cc aacc c aadc dbcd a bca dd abbb ccdcd ccd ab d a a dadcd dbd bcaa c cda b ddab caaaa cdcdb b acbc ccaa dabca dcd b ba dbcc da bdbcc ab abaca bb cddc caca da dadba accdd bdac dbcd bcbbd ab bd ccb ddaa aa b b d bddd cabac aaba ab ccdb db abbd ada bdadb c abba dd cdb bca cccda badba abaa ac aabad db ccbad bddd ada dba acba b bc dd bbbbd cc cbdd cd abcaa bb ddaca acadb bbbb bddcc bdada aaa bcbda c aaa aadd cdddc adb cdbab c cbca bb aacab acdb bbdab b acbda cbdcd bda bacdc db d adcbd bccc c aaa cdd bdcd bac a aaab ddbb cd ccdbb addcc cdc c ca baadc addba dbdbd dba bbdda bcb c cdad aacac dcada cb aaad a cccab caca aad bbb dd b babbb cba bdaca db bacd bc bcbda cdda bcccd bdcda bdbcd adb cbcb a c bacba abbb adab adab b b d bca badbc baa cdb b abc aabb b d c cdab cacda d cdcda adcdc bcc bbccd b adb caba cbaaa aadb dcc add bcac bacbd bb a b c cabaa c caad c aa bcc ccab ddc dadca cdcba aaba dabbd dcb a bddb bb a c c cbc ccd dd a cabbb b caadb cb dca cbb ddaa bcadc dab a bbda cd bc ccad bbd ab c acddd cdd dbbbb daaab abbb cabc add ca caa bbbb dcab daaaa baca dcd ccacb ba bddaa acac dbcc bcc cbbcc b abba daa dbab bcca ba aa d dcdc d dcaa cbcda bd b ccbcb baa dcacd d c cbda baba d abb c cbdc da dbbb cd aabc dadc b a ddb c ddd ccdc ccd cba dbaac dcccd ddbac dbbdd bad bcdd cb dac dccd d a acdd d c cb b bcbb c a aca bcba d d bbdbc d c dabad ccca dc adb ddb dcdd dba ad ddaba c ac ddac bbbd cd a dacbb 1
---
6
adbcb
'''

import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        wordsDict = []
        brotherDict = {}

        lines = line.split()
        lenDict = int(lines[0])

        if len(lines) > 1:
            searchWord = lines[-2]
            searchIndex = int(lines[-1])

            for i in xrange(lenDict):
                word = lines[i+1]
                wordsDict.append(word)

                brotherKey = "".join(sorted(word))
                brotherRecord = brotherDict.setdefault(brotherKey, [])
                brotherRecord.append(word)
        else:
            for i in xrange(lenDict):
                word = sys.stdin.readline().strip()
                wordsDict.append(word)
                
                brotherKey = "".join(sorted(word))
                brotherRecord = brotherDict.setdefault(brotherKey, [])
                brotherRecord.append(word)
            searchWord = sys.stdin.readline().strip()
            searchIndex = int(sys.stdin.readline().strip())

        # print wordsDict

        brotherKey = "".join(sorted(searchWord))
        brotherRecord = sorted(brotherDict.get(brotherKey, []))
        brotherCount = 0
        brotherWord = ""

        for v in brotherRecord:
            if v == searchWord:  # remove self
                continue
            brotherCount += 1
            if brotherCount == searchIndex:
                brotherWord = v

        print "%d\n%s" % (brotherCount, brotherWord)
except:
    pass