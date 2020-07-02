#include "vector3d.h"
#include "time.h"
#include "../binary_mark/bitmark.h"
#include <cmath>
#include <iostream>
using namespace std;

#define PLAYER_NUM 1024
Vector3D *playerVectors[PLAYER_NUM];                        // 堆上零散的内存空间
#define PLAYER_MOVE 1024
CBitMark *pBitMark;

// L1 cache 32KB
// 所有的坐标容量 4 * 3 * 1024 = 12 KB

int main(int argc, char *argv[]) {
    for (int i=0; i<PLAYER_NUM; i++) {
        playerVectors[i] = new Vector3D();          // 堆中不同区域
    }
    
    vector<Vector3D *> visited;
    visited.push_back(playerVectors[0]);

    int sum = 0;
    for (int i=1; i<PLAYER_NUM; i++) {
        for (int j=0; j<visited.size(); j++) {
            ptrdiff_t dis;
            if (playerVectors[i] > visited[j])
                dis = playerVectors[i] - visited[j];
            else
                dis = visited[j] - playerVectors[i];
            if (dis > 32 * 1024) {
                sum ++;
            }
        }
    }
    cout << sum << endl;

    for (int i=0; i<PLAYER_NUM; i++) {
        delete playerVectors[i];
    }
    return 0;
}