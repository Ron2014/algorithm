import sys
'''
qkvmilhdkmjqjzssjufwxvumeogpywxrixvmyvlbyuiykbzflreihurwcsdjkrhoqybjrljvwuwulmssvtrxfsvkicbnwnmzukssbtpwkdvkheeqyxtpojixxbtmbmwmlpxtwsfnltjusjkmnwzoeqvxoftenbgpystjxrjfeblfcomepsmcdkfoporeeqjobmmmsvpjfqxbtkebkwcmjtycisurvxsvttuyhtlewvdcvmlusbpkvubcvtnsduknupkznzfrbstsklcbzltmxovdcgvpycyejlsqoxhluucwocskmwxvcggzyhfcccqmcszniyypeocfkvtwuswcnynkuevgjmlwjutlgzkqsvlphsphligvqnfyrsqsnbooxecprzclqrczjimqcghtbpeovqfngjnyxyeknopsltwvibduwhtxctwqixckxxojegcrugpsqhhmpehsojobvglisylvspkgcyqebmkmohepnizjwttqvnsscgvzpqgfwfhkunpqlvvrfbpxglvnzduzsutixzkhugoixsisodxrpeqbqqwhouimrexktctwqzdspoefeooepctyestcrfxfluwxmjwogubedhdljisfmrboqcihxxjnscxwxgeftrnhvzdyiriivpsixwykydesyursbcuvvoqelyebqbcoutjnehflluqsrpprzktkgdcqnqokdhbwiccfljkukmhszexxgdfwtdonetfkfelxzsrsvbqgxyiykjvprqwfncjvimefetzftfjviiykfwmjsljpszheotouxqlvkbgkkjhecrixhxlgsemtfqfgdyfuivgiptnsmbsnuiiownshvvgdzhljztkvtbofjnpgbqlfbotrlzrdrxownjdkghsubbpzksurplcgxddfxfjiofmwtunqqgxfycoxrvwitvbcffbpimcrrcwrpbdyermztnwssxkzjqrgdmwzxdrmizsqqvdjvhzodhgstfzvktozikbiigkkszyoospiyjcsonjykrtmkcougzcjuodxbndwmwebbxmktqpzkwujedstlvjwnkfxiqgpeiqfhwbqlpprjzeswlyvgkkbwsemmbdmvzumovdqnuzjfbkhbxupwxlzqflyuefzjhdjsqythfjzedznuvqcdenqugzzhnzktrgokmfirdvnqlyxvsefevwpwwdeedogxetuqtqlqownqtojmvyidljsvwbfndssxjtlngqdqrcqlzqcojnphvvwcjmrebkenurdemjoicnquqfzhpwbbqbfisersjpodpvklypjnnwyfeputelulpppuotnepmptxr
---
5
'''

line = ""
line_len = 0

def centerMaxLength(zone_l, zone_r, maxLen):
    if (zone_l > zone_r):
        return maxLen

    pos_m = (zone_l + zone_r) / 2
    # print "center", pos_m
    pos_l = pos_m - 1
    pos_r = pos_m + 1

    new_maxLen = 1
    while(pos_l>=0 and pos_r<line_len and line[pos_l]==line[pos_r]):
        new_maxLen += 2
        pos_l -= 1
        pos_r += 1
    
    l_maxLen = centerMaxLength(zone_l, pos_m-1, maxLen)
    r_maxLen = centerMaxLength(pos_m+1, zone_r, maxLen)
    return max(maxLen, new_maxLen, l_maxLen, r_maxLen)

def nocenterMaxLength(zone_l, zone_r, maxLen):
    if (zone_l > zone_r):
        return maxLen

    pos_m = (zone_l + zone_r) / 2
    # print "nocenter", pos_m
    pos_l = pos_m
    pos_r = pos_l + 1

    new_maxLen = 0
    while(pos_l>=0 and pos_r<line_len and line[pos_l]==line[pos_r]):
        new_maxLen += 2
        pos_l -= 1
        pos_r += 1
    
    l_maxLen = nocenterMaxLength(zone_l, pos_m-1, maxLen)
    r_maxLen = nocenterMaxLength(pos_m+1, zone_r, maxLen)
    return max(maxLen, new_maxLen, l_maxLen, r_maxLen)

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        line_len = len(line)
        pos_l = 0
        pos_r = line_len - 1
        print max(centerMaxLength(pos_l, pos_r, 0), nocenterMaxLength(pos_l, pos_r, 0))
except:
    pass