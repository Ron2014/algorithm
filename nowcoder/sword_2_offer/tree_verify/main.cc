#include "../test.h"

/**
 * 二叉搜索树：
 * 左子树 <= 根 <= 右子树
*/
class Solution {
public:
    bool _VerifySquenceOfBST(vector<int>::iterator seq_begin, int len) {
        if (len==0) return false;
        if (len<3) return true;

        int root = *(seq_begin+len-1);
        int root_pos = 0;
        while (root_pos<len-1) {
            if (*(seq_begin+root_pos)>root) break;
            root_pos++;
        }

        for(int i=root_pos+1; i<len-1; i++) {
            if (*(seq_begin+i)<=root) return false;
        }

        bool ret = true;
        if (root_pos>0) ret &= _VerifySquenceOfBST(seq_begin, root_pos);
        if (root_pos<len-1) ret &= _VerifySquenceOfBST(seq_begin+root_pos, len-root_pos-1);
        return ret;
    }

    bool VerifySquenceOfBST(vector<int> sequence) {
        return _VerifySquenceOfBST(sequence.begin(), sequence.size());
    }
};

int main() {
    int iCount;
    Solution s;
    while (cin>>iCount) {
        INPUT_ARRAY(aNums, iCount, int);
        vector<int> vNums(aNums, aNums+iCount);

        if (s.VerifySquenceOfBST(vNums)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}