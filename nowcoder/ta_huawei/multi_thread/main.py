import threading, sys

THREAD_COUNT = 4
isFinished = False
mutex = threading.Lock()

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
        global g_write, mutex, isFinished, THREAD_COUNT
        count = self.__args
        while True:
            if self.__leader:
                if count==0:
                    break
            else:
                if isFinished:
                    return

            if mutex.acquire(1):
                if len(g_write)%THREAD_COUNT != self.__id:
                    test_print("thread", self.__id, "wait")
                    mutex.release()
                    continue
                test_print("thread", self.__id, "work")
                g_write.append(chr(ord('A')+self.__id))
                if self.__leader: count-=1
                mutex.release()

        if self.__leader:
            while True:
                if mutex.acquire(1):
                    if len(g_write) < self.__args*THREAD_COUNT:
                        test_print("thread", self.__id, "wait finish")
                        mutex.release()
                        continue
                    test_print("thread", self.__id, "set finish")
                    isFinished = True
                    mutex.release()
                    break

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
    