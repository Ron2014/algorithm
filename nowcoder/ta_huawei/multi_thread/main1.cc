#include <pthread.h>
#include "../test.h"

#define THREAD_COUNT 4

pthread_t aThread[THREAD_COUNT];
pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char g_write[1032];
int g_len = 0;
int args[THREAD_COUNT*2];
bool isFinished;

void * ThreadFun(void *pM) {
    int *args = (int *)pM;
    int threadID = args[0];
    int n = args[1];
    if (threadID==0) n++;
    
    while ((threadID==0 && n--) || (threadID!=0 && !isFinished)) {
        pthread_mutex_lock(&lock_mutex);

        while(g_len%THREAD_COUNT!=threadID) {
            if (isFinished) {
                pthread_mutex_unlock(&lock_mutex);
                return (void *)0;
            }
            TEST_INFO2(thread, threadID, "wait");
            pthread_cond_wait(&cond, &lock_mutex);
        }

        if (threadID==0 && n==0) {
            isFinished = true;
            TEST_INFO2(thread, threadID, "set finished");

        } else {
            TEST_INFO2(thread, threadID, "awake to execute");
            g_write[g_len++] = 'A' + threadID;
        }

        pthread_mutex_unlock(&lock_mutex);
        pthread_cond_broadcast(&cond);
    }

    return (void *)0;
}

// void * ThreadFun(void *pM) {
//     int *args = (int *)pM;
//     int threadID = args[0];
//     int n = args[1];
    
//     while ((threadID==0 && n--) || (threadID!=0 && !isFinished)) {
//         pthread_mutex_lock(&lock_mutex);

//         while(g_len%THREAD_COUNT!=threadID) {
//             if (isFinished) {
//                 TEST_INFO2(thread, threadID, "suicide");
//                 pthread_mutex_unlock(&lock_mutex);
//                 return (void *)0;
//             }
//             TEST_INFO2(thread, threadID, "wait");
//             pthread_cond_wait(&cond, &lock_mutex);
//         }

//         TEST_INFO2(thread, threadID, "awake to execute");
//         g_write[g_len++] = 'A' + threadID;

//         pthread_mutex_unlock(&lock_mutex);
//         pthread_cond_broadcast(&cond);
        
//     }

//     if (threadID==0) {
//         pthread_mutex_lock(&lock_mutex);
//         while(g_len<args[1]*THREAD_COUNT) {
//             TEST_INFO2(thread, threadID, "wait to finish");
//             pthread_cond_wait(&cond, &lock_mutex);
//         }
//         TEST_INFO2(thread, threadID, "awake to finish");
//         isFinished = true;
//         pthread_mutex_unlock(&lock_mutex);
//         pthread_cond_broadcast(&cond);
//     }
//     return (void *)0;
// }

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        isFinished = false;
        g_len = 0;

        int err;
        for (int i=0; i<THREAD_COUNT; i++) {
            args[i*2] = i;
            if (i==0) args[i*2+1] = n;
            err = pthread_create(&aThread[i], NULL, ThreadFun, &args[i*2]);
            if (err) cout << "thread" << i << " is dead" << endl;
        }

        for (int i=0; i<THREAD_COUNT; i++) {
            pthread_join(aThread[i], NULL);
        }

        g_write[g_len]= '\0';
        cout << g_write << endl;
    }
    return 0;
}