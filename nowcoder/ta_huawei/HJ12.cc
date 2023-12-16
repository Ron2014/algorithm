#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    char line[1001];
    std::cin.getline(line, sizeof(line));
    int i = 0, j = strlen(line) - 1;
    while (i < j)
    {
        char tmp = line[i];
        line[i] = line[j];
        line[j] = tmp;
        i++;
        j--;
    }
    cout << line << endl;

    return 0;
}