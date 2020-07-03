#include <string>
#include <vector>
using namespace std;

std::string getExtension(const std::string& fileName, bool includeDot = false);
void searchFilesByType(const string &path, const string &type, vector<string> &files);