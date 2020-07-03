#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <time.h>
#include "SimpleIni.h"
#include "path.h"
#include "upenv.h"
using namespace std;

#define CONFIG "config.ini"
#define DATA "data.ini"
#define BUF_LEN 256

struct Node {
    string name;
    string filepath;
    time_t tm;
};

vector<string> files;
map<string, Node*> datas;
time_t livetime;
int next_idx;

int getFileIdx(const string &filepath) {
    auto it = find(files.begin(), files.end(), filepath);
    if (it!=files.end()) return it-files.begin();
    return -1;
}

void updateData(string &filepath, time_t &tm, time_t now, Node *node) {
    if (node && node->tm > now - livetime) {
        // dont need update
        filepath = node->filepath;
        tm = node->tm;
    } else {
        next_idx = (next_idx + 1) % (files.size());
        filepath = files[next_idx];
        tm = now;
    }
}

// 真的会莫名其妙关掉一些窗口, 还是不要用
HWND GetConsoleHwnd(void)
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                        // WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                        // WindowTitle.

    // Fetch current window title.

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.

    wsprintf(pszNewWindowTitle,"%d/%d",
                GetTickCount(),
                GetCurrentProcessId());

    // Change current window title.

    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.

    Sleep(1);

    // Look for NewWindowTitle.

    hwndFound = FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}

int main(int argc, char *argv[]) {  
	HWND hwnd = GetConsoleHwnd();
	ShowWindow(hwnd, false);

    string path = getPath(__FILE__);
#ifdef _WIN32
    SetCurrentDirectory(path.c_str());
#else
    chdir(path.c_str());
#endif

    freopen("./out.log", "w", stdout);
    freopen("./err.log", "w", stderr);

	bool utf8 = true;
	bool multiKey = true;
    CSimpleIniA config(utf8, multiKey);

    // load from a data file
    SI_Error rc = config.LoadFile(CONFIG);
    if (rc != SI_OK) {
        cout << "loading " << CONFIG << " ERROR" << endl;
        fclose(stdout);
        fclose(stderr);
        return 1;
    }
    
    livetime = atoll(config.GetValue("TIME_OUT", "livetime"));

	CSimpleIniA::TNamesDepend pathes;
    config.GetAllValues("PATH", "path", pathes);
	pathes.sort(CSimpleIniA::Entry::LoadOrder());

	CSimpleIniA::TNamesDepend types;
    config.GetAllValues("TYPE", "type", types);
	types.sort(CSimpleIniA::Entry::LoadOrder());

	CSimpleIniA::TNamesDepend names;
    config.GetAllValues("NAME", "name", names);
	names.sort(CSimpleIniA::Entry::LoadOrder());

	CSimpleIniA::TNamesDepend::const_iterator it0;
	CSimpleIniA::TNamesDepend::const_iterator it1;
    files.clear();
	for (it0 = pathes.begin(); it0 != pathes.end(); ++it0) {
		for (it1 = types.begin(); it1 != types.end(); ++it1) {
            searchFilesByType(it0->pItem, it1->pItem, files);
        }
	}
    sort(files.begin(), files.end());

    CSimpleIniA data(utf8, !multiKey);
    rc = data.LoadFile(DATA);

    datas.clear();
    next_idx = 0;

	CSimpleIniA::TNamesDepend::const_iterator it3;
    if (rc == SI_OK) {
	    for (it3 = names.begin(); it3 != names.end(); ++it3) {
            if (!data.GetSection(it3->pItem)) continue;
            Node *node = new Node;
            node->name = it3->pItem;
            node->filepath = data.GetValue(it3->pItem, "filepath");
            node->tm = atoll(data.GetValue(it3->pItem, "tm"));
            datas.insert({node->name, node});
            int idx = getFileIdx(node->filepath);
            if (idx > next_idx) next_idx = idx;
        }
    }

    char s_tmp[BUF_LEN];
    time_t now = time(NULL);
	for (it3 = names.begin(); it3 != names.end(); ++it3) {
        string filepath;
        time_t tm;
        updateData(filepath, tm, now, datas[it3->pItem]);
        
        // modify data
        data.SetValue(it3->pItem, "filepath", filepath.c_str());
        snprintf(s_tmp, BUF_LEN, "%lld", tm);
        data.SetValue(it3->pItem, "tm", s_tmp);

        // modify system environment variable

        // 1. system call
        // snprintf(s_tmp, BUF_LEN, "set %s=\"%s\"", it3->pItem, filepath.c_str());
        // system(s_tmp);

        // 2. win32 API
        // snprintf(s_tmp, BUF_LEN, "\"%s\"", filepath.c_str());
        // bool suc = SetEnvironmentVariable(it3->pItem, s_tmp);
        // if (!suc) cout << GetLastError() << endl;

        // 3. putenv
        // snprintf(s_tmp, BUF_LEN, "%s=\"%s\"", it3->pItem, filepath.c_str());
        // putenv(s_tmp);
        
        // snprintf(s_tmp, BUF_LEN, "\"%s\"", filepath.c_str());
        setEnvVar(it3->pItem, filepath.c_str());
    }

    // save file
    rc = data.SaveFile(DATA);
    if (rc != SI_OK) {
        cout << "SAVING " << DATA << " ERROR" << endl;
        fclose(stdout);
        fclose(stderr);
        return 1;
    }

    fclose(stdout);
    fclose(stderr);
    return 0;
}