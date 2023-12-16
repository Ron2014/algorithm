import sys

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    
    result = []
    fen_zi, fen_mu = map(int, line.split("/"))
    idx = 0

    while fen_zi > 1:
        if fen_mu % (fen_zi-1):
            idx = fen_mu / fen_zi + 1
            fen_zi = fen_zi * idx - fen_mu
            fen_mu = fen_mu * idx
            result.append("1/%d" % (idx))

            for i in range(fen_zi/2,2,-1):
                if fen_zi%i==fen_mu%i==0:
                    fen_zi = fen_zi / i
                    fen_mu = fen_mu / i
                    break
        else:
            result.append("1/%d"%(fen_mu/(fen_zi-1)))
            fen_zi = 1

    result.append("1/%d"%(fen_mu))
    print("+".join(result))
        