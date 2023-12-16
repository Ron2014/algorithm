#include <memory.h>

class Solution {
public:
	void replaceSpace(char *str, int length) {
        // ' ' -> '%20' : 2 more char
        int new_length = length;
        for (int i=0; i<length; i++)
            if (str[i]==' ') new_length+=2;

        // realloc : change the pointer itself
        str = (char *)realloc(str, sizeof(char)*new_length);
        
        // copy from tail
        int s_pos = length;
        int t_pos = new_length;
        while(s_pos--) {
            if (str[s_pos]==' ') {
                str[--t_pos] = '0';
                str[--t_pos] = '2';
                str[--t_pos] = '%';
            } else {
                str[--t_pos] = str[s_pos];
            }
        }
	}
};