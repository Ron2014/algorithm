import threading, sys

THREAD_COUNT = 4
isFinished = False
conds = []
for i in xrange(THREAD_COUNT):
    conds.append(threading.Condition())

def test_print(*args):
    count = len(args)
    sys.stderr.write( ("%s "*count + '\n') % (args))

class MyThread(threading.Thread):
    def __init__(self, id, leader, args=None):
        super(MyThread, self).__init__()
        self.__id = id
        self.__leader = leader
        self.__args = args

    def run(self):
        global g_write, isFinished, THREAD_COUNT, conds
        id = self.__id
        isLeader = self.__leader

        count = self.__args
        cond = conds[self.__id]

        while True:
            if isFinished:
                return

            if cond.acquire(True):
                while len(g_write)%THREAD_COUNT != id:
                    test_print("thread", id, "wait")
                    if isFinished:
                        cond.release()
                        return
                    cond.wait()

                if isLeader:
                    if count==0:
                        test_print("thread", id, "set finish")
                        isFinished = True
                        cond.release()
                        for i in xrange(THREAD_COUNT):
                            next_cond = conds[i]
                            if next_cond.acquire(True):
                                next_cond.notify()
                                next_cond.release()
                        continue

                test_print("thread", id, "work")
                g_write.append(chr(ord('A')+id))
                if isLeader: count-=1
                cond.release()

                next_cond = conds[(id+1)%THREAD_COUNT]
                if next_cond.acquire(True):
                    next_cond.notify()
                    next_cond.release()

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    count = int(line.split()[0])
    g_write = []
    isFinished = False

    threads = []
    for i in xrange(THREAD_COUNT):
        threads.append(MyThread(i, i==0, count if i==0 else None))
    for i in xrange(THREAD_COUNT):
        threads[i].start()
    for i in xrange(THREAD_COUNT):
        threads[i].join()
    print("".join(g_write))
    