#include <pthread.h>
#include "../test.h"

#define THREAD_COUNT 4

pthread_t aThread[THREAD_COUNT];
pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// pthread_mutex_t aMutex[THREAD_COUNT];
// pthread_cond_t aCond[THREAD_COUNT];

/***********************************************
这个故事应该是这样的：
随着自然环境越来越恶化，每个村子需要自发组织安检工作
现上级安排的安检流程如下：
1. 安检人员都是该村的村民
2. 安检是轮班制，单位为天
3. 安检人员仅一人
4. 轮到当天值班的安检人员，无论是什么身份，都得放下本职工作，专心做好该村当天的安检
5. 每天的工作结束后，安检人员需要在值班表上签名
6. 村民中会选出一人作为安检队长
7. 安检工作有个暂定的期限，期限结束之后，安检队长需要上交值班表
8. 只有安检队长知道安检工作的期限，其他村民都不知道
9. 安检工作的第一天从队长开始
10. 上级可以根据需要提供一定数量的对讲机，用于安检工作中的通信
11. 值班表上交后，上级有权利决定，是否开启新的安检周期，或者结束安检

现有一个村子住着 A B C D 四个村民，上级指派了 A 作队长，并告诉其暂定的期限。
请你设计一个程序，去模拟上述的过程。并回答以下内容分别对应计算机的什么操作或概念？

1. 上级
2. 村民
3. 当天的安检人员
4. 安检队长
5. 值班表
6. 值班表的上交
7. 对讲机
8. 通信

输入：
案件期限

输出：
期限结束后，上级会受到的值班表的内容（签名彼此相连，中间没有空格）
***********************************************/

char g_write[1032];                                //线程1,2,3,4按顺序向该数组赋值。不用考虑数组是否越界，测试用例保证
int g_len = 0;
int args[THREAD_COUNT*2];
bool isFinished;

void * ThreadFun(void *pM) {
    int *args = (int *)pM;
    int threadID = args[0];
    int n = args[1];
    
    while (true) {
        if (threadID>0) {
            if (isFinished) break;
        } else {
            if (!n--) break;
        }
        // pthread_mutex_lock(&aMutex[threadID]);
        pthread_mutex_lock(&lock_mutex);
        while(g_len%THREAD_COUNT!=threadID) {
            // pthread_cond_wait(&aCond[threadID], &aMutex[threadID]);
            if (isFinished) {
                TEST_INFO2(thread, threadID, "suicide");
                pthread_mutex_unlock(&lock_mutex);
                return (void *)0;
            }
            TEST_INFO2(thread, threadID, "wait");
            // pthread_cond_wait(&aCond[threadID], &lock_mutex);
            pthread_cond_wait(&cond, &lock_mutex);
        }

        // pthread_mutex_lock(&lock_mutex);

        TEST_INFO2(thread, threadID, "awake to execute");
        g_write[g_len++] = 'A' + threadID;

        // pthread_mutex_unlock(&aMutex[threadID]);
        pthread_mutex_unlock(&lock_mutex);
        // pthread_cond_signal(&aCond[(threadID+1)%THREAD_COUNT]);
        // pthread_cond_signal(&aCond[0]);
        pthread_cond_broadcast(&cond);
        
    }
    finished:
    if (threadID==0) {
        // pthread_mutex_lock(&aMutex[threadID]);
        pthread_mutex_lock(&lock_mutex);
        while(g_len<args[1]*THREAD_COUNT) {
            // pthread_cond_wait(&aCond[threadID], &aMutex[threadID]);
            TEST_INFO2(thread, threadID, "wait to finish");
            // pthread_cond_wait(&aCond[threadID], &lock_mutex);
            pthread_cond_wait(&cond, &lock_mutex);
        }
        TEST_INFO2(thread, threadID, "awake to finish");
        isFinished = true;
        // pthread_mutex_lock(&aMutex[threadID]);
        pthread_mutex_unlock(&lock_mutex);
        // for (int i=1; i<THREAD_COUNT;i ++)
        //     pthread_cond_signal(&aCond[threadID+i]);
        pthread_cond_broadcast(&cond);
    }
    return (void *)0;
}

int main() {
    // for (int i=0; i<THREAD_COUNT; i++) {
    //     aMutex[i] = PTHREAD_MUTEX_INITIALIZER;
    //     aCond[i] = PTHREAD_COND_INITIALIZER;
    // }

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

        for (int i=0; i<THREAD_COUNT; i++) {
        // for (int i=THREAD_COUNT-1; i>=0; i--) {
            pthread_join(aThread[i], NULL);
        }

        g_write[g_len]= '\0';
        cout << g_write << endl;
    }
    return 0;
}