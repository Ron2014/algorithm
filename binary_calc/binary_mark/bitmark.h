#include <vector>
#include <cstdlib>
using namespace std;

class CBitMark {
    unsigned char *data = nullptr;
    size_t bsize;
public:
    CBitMark(size_t capacity);
    ~CBitMark();
    void Extend(size_t capacity);
    void Mark(size_t slot);
    void Unmark(size_t slot);
    void Display();
    vector<size_t> GetMarkList();
};