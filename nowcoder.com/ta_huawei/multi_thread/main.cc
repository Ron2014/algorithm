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

bool isFinished;

char g_write[1032];
int g_len = 0;

int args[THREAD_COUNT*2];

unsigned int Thread(void *pM) {
    // doing something
    int *args = (int *)pM;
    int threadID = args[0];
    int n = args[1];

    while ((threadID==0 && n--) || (threadID!=0 && !isFinished)) {
        unique_lock <mutex> lck(lock_mutex);
        while (g_len % THREAD_COUNT!=threadID) {
            if(isFinished) {
                TEST_INFO2(thread, threadID, "suicide");
                return 0;
            }
            TEST_INFO2(thread, threadID, "wait");
            cond.wait(lck);
        }

        TEST_INFO2(thread, threadID, "awake to execute");
        g_write[g_len++] = 'A' + threadID;
        cond.notify_all();
    }

    if (threadID==0) {
        unique_lock <mutex> lck(lock_mutex);
        while(g_len<args[1]*THREAD_COUNT) {
            TEST_INFO2(thread, threadID, "wait to finish");
            cond.wait(lck);
        }
        TEST_INFO2(thread, threadID, "awake to finish");
        isFinished = true;
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

        for (int i=0;i<THREAD_COUNT;i++) {
            aThread[i]->join();
        }

        g_write[g_len]= '\0';
        cout << g_write << endl;

        Release();
    }
    return 0;
}