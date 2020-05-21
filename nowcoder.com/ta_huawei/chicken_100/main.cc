#include <iostream>
using namespace std;

// x+y+z=100
// 5x+3y+z/3=100

int main() {
    int n;
    while(cin >> n) {
        for(int x=0; x<=100/5; x++) {
            // y+z = 100-x
            // 3y+z/3 = 100-5x

            int leftCount = 100 - x;
            int leftMoney = 100 - 5 * x;

            for(int y=0; y<=leftCount; y++) {
                int z = (leftMoney-3*y)*3;
                if (z>=0 && leftCount==z+y)
                    cout << x << " " << y << " " << z << endl;
            }
        }
    }
    return 0;
}