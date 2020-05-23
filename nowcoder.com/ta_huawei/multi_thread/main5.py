import threading, sys

THREAD_COUNT = 4
WEEK_DAYS = 7
MEETTING_DAY = 5
SEPARATE_DAYS = 15

isFinished = False
count = 0
threads = []
g_write = []

circle_count = 0
circle_sign = 0

conds = []
for i in xrange(THREAD_COUNT):
    conds.append(threading.Condition())
# cond_lock = threading.Condition()
cond_lock = threading.Lock()
m_lock = threading.Lock()

duty = []
separates = set([])

def has_meetting(start_weekday):
    return (start_weekday+len(g_write)) % WEEK_DAYS == MEETTING_DAY

def get_lowest_one():
    global g_write, separates
    stat = {}
    for n in g_write:
        ni = ord(n)-ord('A')
        stat[ni] = stat.get(ni, 0) + 1
    key_list = stat.keys()
    sorted(key_list, key=lambda x: x + stat.get(x, 0)*2)
    for n in key_list:
        if n not in separates:
            return n

def switch_duty(i, j):
    global duty
    ii = duty.index(i)
    ij = duty.index(j)
    duty[ii], duty[ij] = duty[ij], duty[ii]

def add_duty(i):
    global duty
    assert(i not in duty, "add_duty error")
    duty.insert(len(g_write) % len(duty), i)
    return True

def rem_duty(i):
    global duty
    assert(i in duty, "rem_duty error")
    duty.remove(duty.index(i))
    return True

def is_weak(weak_day):
    # test_print("is_weak", weak_day, "".join(g_write))
    if weak_day is None:
        return False
    return len(g_write)>=weak_day and len(g_write)<(weak_day+SEPARATE_DAYS)

def test_print(*args):
    return 
    sys.stderr.write("".join("%s "*len(args) % (args))+"\n")
    
class MyThread(threading.Thread):
    def __init__(self, id, leader, weak_day):
        super(MyThread, self).__init__()
        self.__id = id
        self.__weak_day = weak_day
        self.is_leader = leader
        self.left_separate = 0
    
    def exchange(self, next_id):
        switch_duty(self.__id, next_id)
    
    def getWeakDay(self):
        return self.__weak_day
    
    def setLeader(self, isLeader):
        self.is_leader = isLeader

    def run(self):
        global g_write, isFinished, conds, cond_lock, m_lock, circle_count, circle_sign, separates, threads, THREAD_COUNT, SEPARATE_DAYS
        id = self.__id
        weak_day = self.__weak_day
        origin_leader = self.is_leader

        cond = conds[id]
        lock = cond_lock
        meetting = False

        while True:
            if isFinished:
                break

            if cond.acquire(True):
                while id in separates and is_weak(weak_day):
                    test_print("thread", id, "is separate")
                    cond.wait()
                cond.release()

                test_print("thread", id, "is awake")
                if lock.acquire(True):

                    # test_print("thread", id, "enter ........")
                    cur_idx = len(g_write)%len(duty)
                    next_idx = (len(g_write)+1)%len(duty)
                    last_idx = (len(g_write)-1)%len(duty)

                    if id in separates:
                        test_print("thread", id, "leave hospital")

                        separates.discard(id)
                        add_duty(id)

                        cur_idx = len(g_write)%len(duty)
                        while duty[cur_idx] != id:
                            n = duty.pop()
                            duty.insert(0, n)
                        test_print("thread", id, "change duty to", ",".join(map(str, duty)))

                        if origin_leader:
                            for i, t in enumerate(threads):
                                if i!=id:
                                    t.setLeader(False)
                        else:
                            self.is_leader = False
                    else:
                        # make room for backflow
                        someone_is_leaving_hospital = False
                        for oid in separates:
                            if not is_weak(threads[oid].getWeakDay()):
                                someone_is_leaving_hospital = True
                                break
                        if someone_is_leaving_hospital:
                            lock.release()
                            continue

                    if duty[cur_idx] != id:
                        # test_print("thread", id, "wait")
                        lock.release()
                        continue
                    
                    # test_print("thread", id, "do something .......................")
                    next_idx = (len(g_write)+1)%len(duty)
                    next_id = duty[next_idx]

                    if is_weak(weak_day):
                        # sperate
                        test_print("thread", id, "goto hospital")
                        separates.add(id)
                        rem_duty(id)
                            
                        if origin_leader or self.is_leader:
                            new_leader_id = get_lowest_one()
                            threads[new_leader_id].setLeader(True)
                            test_print("thread", id, "set new leader", new_leader_id)

                        next_idx = len(g_write)%len(duty)
                        while duty[next_idx] != next_id:
                            n = duty.pop()
                            duty.insert(0, n)
                        test_print("thread", id, "change duty to", ",".join(map(str, duty)))

                        lock.release()
                        continue

                    if self.is_leader:
                        global count, weekday
                        if has_meetting(weekday):
                            test_print("thread", id, "has meetting, wait exchange with", next_id)
                            meetting = True
                            threads[next_id].exchange(id)
                            test_print("thread", id, "change duty to", ",".join(map(str, duty)))

                            lock.release()
                            continue

                        if meetting:
                            meetting = False
                            threads[duty[last_idx]].exchange(id)
                            test_print("thread", id, "change duty to", ",".join(map(str, duty)))

                        if circle_count>=count:
                            test_print("thread", id, "set finish")
                            isFinished = True
                            lock.release()
                            continue

                    g_write.append(chr(ord('A')+id))
                    test_print("thread", id, "work", "".join(g_write))

                    circle_sign += 1
                    if circle_sign >= len(duty):
                        test_print("thread", id, "get signed", circle_sign, "and add circle", circle_count+1)
                        circle_sign = circle_sign % len(duty) 
                        circle_count += 1

                    lock.release()

                    nsep = set(separates)
                    for sid in nsep:
                        if conds[sid].acquire(True):
                            test_print("thread", id, "notify", sid)
                            conds[sid].notify()
                            conds[sid].release()

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])
    if len(lines) > 1:
        weekday, weak_name, weak_day = int(lines[1]), lines[2], int(lines[3])
    else:
        weekday = int(sys.stdin.readline().strip()) % WEEK_DAYS
        weak_name = sys.stdin.readline().strip()
        weak_day = int(sys.stdin.readline().strip())

    g_write = []
    isFinished = False
    weak_idx = ord(weak_name) - ord('A')
    
    duty = []
    for i in xrange(THREAD_COUNT):
        duty.append(i)

    test_print(",".join(map(str,duty)))
    separates = set([])
    circle_count = 0
    circle_sign = 0
    
    threads = []
    for i in xrange(THREAD_COUNT):
        threads.append(MyThread(i, i==0, weak_day if i==weak_idx else None))
    for i in xrange(THREAD_COUNT):
        threads[i].start()
    for i in xrange(THREAD_COUNT):
        threads[i].join()
    print("".join(g_write))
    