#include <stack>
#include <iostream>
using namespace std;

class Solution
{
public:
    // to tail
    void push(int node) {
        stack2.push(node);
    }

    // from head
    int pop() {
        if (stack1.empty()) {
            // reverse stack2
            while (!stack2.empty()) {
                stack1.push(stack2.top());
                stack2.pop();
            }
        }
        int ret = -1;
        if (!stack1.empty()) {
            ret = stack1.top();
            stack1.pop();
        }
        return ret;
    }

private:
    stack<int> stack1; // head
    stack<int> stack2; // tail
};

int main() {
    char command;
    Solution s;
    int n;
    while (std::cin>>command) {
        switch(command) {
            case 'd':   // dequeue
                std::cout << s.pop() << endl;
                break;
            case 'e': { // enqueue
                std::cin >> n;
                s.push(n);
            }   break;
        }
    }
    return 0;
}