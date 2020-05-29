#include "../test.h"
#include <iostream>
#include <memory.h>
using namespace std;

struct Task {
    int x;          // time
    int y;          // level
};

struct Robot {
    int z;          // max work time
    int w;          // level
};

int reward(Task &t) {
    return 200 * t.x + 3 * t.y;
}

bool cmpTask(Task &a, Task &b) {
    int w0, w1, step;
    w0 = w1 = 0;
    step = 1;

    if (reward(a) > reward(b)) w0 += step;
    else if (reward(a) < reward(b)) w1 += step;
    step *= 2;

    if (a.y > b.y) w1 += step;
    else if (a.y < b.y) w0 += step;
    step *= 2;

    if (a.x > b.x) w1 += step;
    else if (a.x < b.x) w0 += step;

    return w0 < w1;
}

bool cmpRobot(Robot &a, Robot &b) {
    int w0, w1, step;
    w0 = w1 = 0;
    step = 1;

    if (a.w > b.w) w1 += step;
    else if (a.w < b.w) w0 += step;
    step *= 2;

    if (a.z > b.z) w1 += step;
    else if (a.z < b.z) w0 += step;

    return w0 < w1;
}

int main() {
    int iN, iM;
    while (cin>>iN>>iM) {
        Robot *aRobot = new Robot[iN];
        Task *aTask = new Task[iM];

        for (int i=0; i<iN; i++) {
            cin >> aRobot[i].z;
            cin >> aRobot[i].w;
        }

        for (int i=0; i<iM; i++) {
            cin >> aTask[i].x;
            cin >> aTask[i].y;
        }

        vector<Task> vTask(aTask, aTask+iM);
        sort(vTask.begin(), vTask.end(), cmpTask);
        vector<Robot> vRobot(aRobot, aRobot+iN);
        sort(vRobot.begin(), vRobot.end(), cmpRobot);

        Task t;
        Robot r;
        int left = iN;
        int max_num = 0;
        int max_reward = 0;
        for (int i=iM-1; i>=0; i--) {
            t = vTask[i];
            while(left--) {
                if (vRobot[left].z < t.x)
                    continue;
                if (vRobot[left].w < t.y)
                    continue;
                max_num += 1;
                max_reward += reward(t);
            }
            if (left<=0) break;
        }
        cout << max_num << " " << max_reward << endl;

        /**
         * aMaxNum[i][j] means:
         * use front j robots to finish front i task
        */
/*
        int **aTaskNum = new int*[iM+1];
        for (int i=0; i<=iM; i++) {
            aTaskNum[i] = new int[iN+1];
            memset(aTaskNum[i], 0, sizeof(int)*(iN+1));
        }
        int **aTaskReward = new int*[iM+1];
        for (int i=0; i<=iM; i++) {
            aTaskReward[i] = new int[iN+1];
            memset(aTaskReward[i], 0, sizeof(int)*(iN+1));
        }

        int max_num = 0;
        int max_reward = 0;
        for (int i=1; i<=iM; i++) {
            t = aTask[i-1];   // new task
            for (int j=1; j<=iN; j++) {
                r = aRobot[j-1];   // new robot;
                aTaskNum[i][j] = aTaskNum[i-1][j-1];
                aTaskReward[i][j] = aTaskReward[i-1][j-1];
                if (r.z >= t.x && r.w >= t.y) {
                    aTaskNum[i][j] += 1;
                    aTaskReward[i][j] += reward(t);
                }

                if (aTaskNum[i][j] < aTaskNum[i-1][j]) {
                    aTaskNum[i][j] = aTaskNum[i-1][j];
                    aTaskReward[i][j] = aTaskReward[i-1][j];
                } else if(aTaskNum[i][j] == aTaskNum[i-1][j]) {
                    if (aTaskReward[i][j] < aTaskReward[i-1][j]) {
                        aTaskReward[i][j] = aTaskReward[i-1][j];
                    }
                }

                max_num = (aTaskNum[i][j]>max_num) ? aTaskNum[i][j] : max_num;
                max_reward = (aTaskReward[i][j]>max_reward) ? aTaskReward[i][j] : max_reward;
            }
        }

        SHOW_ARRAY2(aTaskNum, iM+1, iN+1);
        SHOW_ARRAY2(aTaskReward, iM+1, iN+1);
    
        cout << max_num << " " << max_reward << endl;

        for (int i=0; i<=iM; i++)
            delete[] aTaskNum[i];
        delete[] aTaskNum;

        for (int i=0; i<=iM; i++)
            delete[] aTaskReward[i];
        delete[] aTaskReward;
*/
        delete[] aRobot;
        delete[] aTask;
    }

    return 0;
}