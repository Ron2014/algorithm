#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "../test.h"

void Init();        //初始化函数
void Release();     //资源释放函数

#define THREAD_COUNT 4

thread *aThread[THREAD_COUNT];

condition_variable cond;
mutex lock_mutex;

// condition_variable aCond[THREAD_COUNT];
// mutex aMutex[THREAD_COUNT];
bool isFinished;

char g_write[1032];                                //线程1,2,3,4按顺序向该数组赋值。不用考虑数组是否越界，测试用例保证
int g_len = 0;

int args[THREAD_COUNT*2];

unsigned int Thread(void *pM) {
    // doing something
    int *args = (int *)pM;
    int threadID = args[0];
    int n = args[1];

    while (true) {
        if (threadID>0) {
            if (isFinished) break;
        } else {
            if (!n--) break;
        }

        // unique_lock <mutex> lck(aMutex[threadID]);
        unique_lock <mutex> lck(lock_mutex);
        while (g_len % THREAD_COUNT!=threadID) {
            if(isFinished) {
                TEST_INFO2(thread, threadID, "suicide");
                return 0;
            }
            TEST_INFO2(thread, threadID, "wait");
            // aCond[threadID].wait(lck);
            cond.wait(lck);
        }

        TEST_INFO2(thread, threadID, "awake to execute");
        g_write[g_len++] = 'A' + threadID;
        // aCond[(threadID+1)%THREAD_COUNT].notify_one();
        cond.notify_all();
    }

    if (threadID==0) {
        // unique_lock <mutex> lck(aMutex[threadID]);
        unique_lock <mutex> lck(lock_mutex);
        while(g_len<args[1]*THREAD_COUNT) {
            TEST_INFO2(thread, threadID, "wait to finish");
            // aCond[threadID].wait(lck);
            cond.wait(lck);
        }
        TEST_INFO2(thread, threadID, "awake to finish");
        isFinished = true;
        // for (int i=1; i<THREAD_COUNT; i++)
        //     aCond[threadID+i].notify_one();
        cond.notify_all();
    }

    return 0;
}

void Init(int n) {
    g_len = 0;
    isFinished = false;

    for (int i=0;i<THREAD_COUNT;i++) {
        args[i*2] = i;
        if (i==0) args[i*2+1] = n;
        aThread[i] = new thread(Thread, &args[i*2]);
    }
}

void Release() {
    for (int i=0;i<THREAD_COUNT;i++) {
        delete aThread[i];
    }
}

int main() {
    int n;
    while(cin>>n) {
        Init(n);

        // aCond[0].notify_one();
        for (int i=0;i<THREAD_COUNT;i++) {
            aThread[i]->join();
        }

        g_write[g_len]= '\0';
        cout << g_write << endl;

        Release();
    }
    return 0;
}