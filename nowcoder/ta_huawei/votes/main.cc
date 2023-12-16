#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<string, unsigned int> mVotes;
vector<string> vNames;

// 功能：设置候选人姓名
// 输入： char* pCandidateName 候选人姓名
// 输出：无
// 返回：输入值非法返回0，已经添加过返回0 ，添加成功返回1
unsigned int  AddCandidate (const char* pCandidateName) {
    string name = pCandidateName;
    if (mVotes.find(name) != mVotes.end()) return 0;
    mVotes.insert(make_pair(name, 0));
    return 1;
}

 
// 功能：投票
// 输入： char* pCandidateName 候选人姓名
// 输出：无
// 返回：无
unsigned int Vote(const char* pCandidateName) {
    string name = pCandidateName;
    if (mVotes.find(name) == mVotes.end()) return 0;
    mVotes[name]++;
    return 1;

}


// 功能：获取候选人的票数。如果传入为空指针，返回无效的票数，同时说明本次投票活动结束，释放资源
// 输入： char* pCandidateName 候选人姓名。当输入一个空指针时，返回无效的票数
// 输出：无
// 返回：该候选人获取的票数
unsigned int GetVoteResult (const char* pCandidateName) {
    string name = pCandidateName;
    if (mVotes.find(name) == mVotes.end()) return 0;
    return mVotes[name];
}

// 功能：清除投票结果，释放所有资源
// 输入：
// 输出：无
// 返回
void Clear() {
    mVotes.clear();
    vNames.clear();
}

int main() {
    int n, invalid;
    string s;
    while(cin>>n) {
        invalid = 0;
        Clear();
        
        while(n--) {
            cin >> s;
            if(!AddCandidate(s.c_str())) invalid++;
            else vNames.push_back(s);
        }
        cin>>n;
        while(n--) {
            cin >> s;
            if(!Vote(s.c_str())) invalid++;
        }
        for (auto it=vNames.begin(); it!=vNames.end(); it++) {
            cout << *it << " : " << GetVoteResult((*it).c_str()) << endl;
        }
        cout << "Invalid : " << invalid << endl;
    }
    return 0;
}
