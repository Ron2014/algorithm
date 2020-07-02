#include "vector3d.h"
#include "time.h"
#include "../binary_mark/bitmark.h"
#include <cmath>
#include <iostream>
using namespace std;

#define PLAYER_NUM 1024
Vector3D *playerVectors;                                // 堆上的一个连续内存空间
#define PLAYER_MOVE 1024
CBitMark *pBitMark;

void movePlayer(void) {
    for (int i; i<PLAYER_MOVE; i++) {
        int idx = rand() % PLAYER_NUM;
        pBitMark->Mark(idx);
    }
}

void updatePlayer(void) {
    // vector<size_t> list = pBitMark->GetMarkList();

    // 实际中使用脏标记, 但为了遍历最大化, 脏标记也省了
    clock_t now = clock(); 
    // for (size_t pid : list) {
    for(int pid=0; pid<PLAYER_NUM; pid++) {
        playerVectors[pid].x += 0.1f;
        playerVectors[pid].y += 0.1f;
        playerVectors[pid].z += 0.1f;
    }
    cout << clock() - now << endl;
}

int main(int argc, char *argv[]) {
    playerVectors = new Vector3D[PLAYER_NUM];

    srand(0);
    pBitMark = new CBitMark(PLAYER_NUM);
    movePlayer();

    updatePlayer();

    delete pBitMark;
    delete[] playerVectors;
    return 0;
}