#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int iCountOfBasket;
int iCountOfApple;
string **aStoreWays;
char buff[1000];

/***
5 6
---
7

4 1
---
1
*/

// #define TEST

string getWayNode(int &first, string left) {
    int num;
    vector<int> factors;
    factors.push_back(first);
    
    // split
    size_t sepr = left.find(',');
    while(sepr != string::npos) {
        num = atoi(left.substr(0, sepr).c_str());
        factors.push_back(num);
        left = left.substr(sepr+1, left.length()-sepr);
        sepr = left.find(',');
    }
    
    num = atoi(left.c_str());
    factors.push_back(num);

    // sort
    sort(factors.begin(), factors.end());

    // tostring
    std::stringstream ss;
    bool needSepr = false;
    for (auto it=factors.begin(); it!=factors.end(); it++) {
        if (needSepr) ss << ",";
        ss << *it;
        needSepr = true;
    }

    return ss.str();
}

int main() {
    while (cin>>iCountOfApple>>iCountOfBasket) {
        // aStoreWays = new string*[(iCountOfApple+1) * (iCountOfBasket+1)];
        aStoreWays = new string*[iCountOfApple+1];
        for (int i=0; i<=iCountOfApple; i++) {
            aStoreWays[i] = new string[iCountOfBasket+1];
        }

        for (int i=1; i<=iCountOfApple; i++) {
            for (int j=1; j<=iCountOfBasket; j++) {

                if (i==1 || j==1) {
                    sprintf(buff, "%d", i);
                    aStoreWays[i][j] = buff;
                } else if (j > i) {
                    // no more new way if basket > apple
                    aStoreWays[i][j] = aStoreWays[i][j-1];
                } else {
                    stringstream new_ways;
                    bool needSepr = false;

                    for (int k=0; k<=i-1; k++) {
#ifdef TEST
                        cout << i << ' ' << j << ' ' << k << endl;
#endif
                        string sub_way;
                        string left_ways = aStoreWays[i-k][j-1];
                        size_t sepr = left_ways.find(';');

                        while(sepr != string::npos) {
                            sub_way = getWayNode(k, left_ways.substr(0, sepr));
                            if (new_ways.str().find(sub_way) == string::npos) {
                                // not duplicate
                                if (needSepr) new_ways << ";";
                                new_ways << sub_way;
                                needSepr = true;
                            }

                            left_ways = left_ways.substr(sepr+1, left_ways.length()-sepr);
                            sepr = left_ways.find(';');
                        }

                        sub_way = getWayNode(k, left_ways);
                        if (new_ways.str().find(sub_way) == string::npos) {
                            // not duplicate
                            if (needSepr) new_ways << ";";
                            new_ways << sub_way;
                            needSepr = true;
                        }
                    }

                    aStoreWays[i][j] = new_ways.str();
                }
            }
        }

#ifdef TEST
        for (int i=1; i<=iCountOfApple; i++) {
            for (int j=1; j<=iCountOfBasket; j++) 
                cout << i << ',' << j << ' ' << aStoreWays[i][j] << endl;
        }
        cout << endl;
#endif
        string last_ways = aStoreWays[iCountOfApple][iCountOfBasket];
        int num = count(last_ways.begin(), last_ways.end(), ';');
        if (last_ways.length()) num++;
        cout << num << endl;
        
        // for (int i=0; i<=iCountOfApple; i++) {
        //     delete [] aStoreWays;
        // }
        // delete aStoreWays;
        delete [] aStoreWays;
    }
    return 0;
}