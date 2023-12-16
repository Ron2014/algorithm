import threading, sys

THREAD_COUNT = 4
WEEK_DAYS = 7
MEETTING_DAY = 5

isFinished = False
isMeetting = 0
conds = []
for i in xrange(THREAD_COUNT):
    conds.append(threading.Condition())

def test_print(*args):
    return
    count = len(args)
    sys.stderr.write( ("%s "*count + '\n') % (args))

class MyThread(threading.Thread):
    def __init__(self, id, leader, args=None):
        super(MyThread, self).__init__()
        self.__id = id
        self.__leader = leader
        self.__args = args
        self.next_id = None
    
    def exchange(self, next_id):
        self.next_id = next_id

    def run(self):
        global g_write, isFinished, isMeetting, conds, THREAD_COUNT, WEEK_DAYS, MEETTING_DAY, threads
        id = self.__id
        isLeader = self.__leader

        if isLeader:
            count = self.__args[0]
            weekday = self.__args[1]
        cond = conds[self.__id]

        while True:
            if isFinished:
                break

            if cond.acquire(True):
                while (len(g_write)%THREAD_COUNT != id and self.next_id is None) or \
                    (len(g_write)%THREAD_COUNT == id and self.next_id is not None):
                    test_print("thread", id, "wait")
                    if isFinished:
                        break
                    cond.wait()

                if isFinished:
                    cond.release()
                    continue

                next_id = (id+1)%THREAD_COUNT
                if isLeader:
                    while (weekday+len(g_write)) % WEEK_DAYS == MEETTING_DAY:
                        test_print("thread", id, "wait exchange")
                        next_id = 2
                        threads[1].exchange(0)
                        if conds[1].acquire(True):
                            conds[1].notify()
                            conds[1].release()
                        cond.wait()

                    threads[1].exchange(None)

                    if count==0:
                        test_print("thread", id, "set finish")
                        isFinished = True
                        cond.release()
                        continue
                    
                test_print("thread", id, "work")
                g_write.append(chr(ord('A')+id))
                if isLeader:
                    count-=1
                cond.release()

                if self.next_id is not None:
                    next_id = self.next_id
                    
                next_cond = conds[next_id]
                if next_cond.acquire(True):
                    next_cond.notify()
                    next_cond.release()

        if isLeader:
            for i in xrange(1, THREAD_COUNT):
                next_cond = conds[i]
                if next_cond.acquire(True):
                    next_cond.notify()
                    next_cond.release()
while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])
    if len(lines) > 1:
        weekday = int(lines[1])
    else:
        weekday = int(sys.stdin.readline().strip()) % WEEK_DAYS
    g_write = []
    isFinished = False
    isMeetting = 0

    threads = []
    for i in xrange(THREAD_COUNT):
        threads.append(MyThread(i, i==0, (count, weekday) if i==0 else None))
    for i in xrange(THREAD_COUNT):
        threads[i].start()
    for i in xrange(THREAD_COUNT):
        threads[i].join()
    print("".join(g_write))
    
