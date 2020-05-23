#include <pthread.h>
#include <unistd.h>
#include "../test.h"

#define THREAD_COUNT 4

pthread_t aThread[THREAD_COUNT];
pthread_cond_t aCond[THREAD_COUNT];
pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;

char g_write[1032];
int g_len = 0;
int args[THREAD_COUNT*2];
bool isFinished;

void * ThreadFun(void *pM) {
    int *args = (int *)pM;
    int threadID = args[0];
    int n = args[1];
    
    while ((threadID==0 && n--) || (threadID!=0 && !isFinished)) {
        pthread_mutex_lock(&lock_mutex);
        TEST_INFO2(thread, threadID, "get the lock");
        pthread_cond_wait(&aCond[threadID], &lock_mutex);

        TEST_INFO2(thread, threadID, "awake to execute");
        g_write[g_len++] = 'A' + threadID;

        pthread_mutex_unlock(&lock_mutex);
        pthread_cond_signal(&aCond[(threadID+1)%THREAD_COUNT]);
        
    }
    if (threadID==0) isFinished = true;
    return (void *)0;
}

int main() {
    for (int i=0; i<THREAD_COUNT; i++) {
        aCond[i] = PTHREAD_COND_INITIALIZER;
    }

    int n;
    while(scanf("%d", &n) != EOF) {
        isFinished = false;
        g_len = 0;

        int err;
        for (int i=0; i<THREAD_COUNT; i++) {
        // for (int i=THREAD_COUNT-1; i>=0; i--) {
            args[i*2] = i;
            if (i==0) args[i*2+1] = n;
            err = pthread_create(&aThread[i], NULL, ThreadFun, &args[i*2]);
            if (err) cout << "thread" << i << " is dead" << endl;
        }
        // sleep(10);
        // cout << "thread 0 send signal" << endl;
        pthread_cond_signal(&aCond[0]);
        // for (int i=THREAD_COUNT-1; i>=0; i--) {
        for (int i=0; i<THREAD_COUNT; i++) {
            pthread_join(aThread[i], NULL);
        }

        g_write[g_len]= '\0';
        cout << g_write << endl;
    }
    return 0;
}