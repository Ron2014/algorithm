#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <time.h>
// #include <cstdlib>
#include <stdlib.h>
#include "SimpleIni.h"
using namespace std;

#define CONFIG "config.ini"
#define DATA "data.ini"

#if _WIN32
#include <windows.h>
#include <io.h>
#else
#include <errno.h>
#include <dirent.h>
#endif

struct Node {
    string name;
    string filepath;
    time_t tm;
};

vector<string> files;
map<string, Node*> datas;
time_t livetime;
int next_idx;

std::string getExtension(const std::string& fileName, bool includeDot) {
	std::string::size_type dotPos = fileName.rfind(".");
	if (dotPos != std::string::npos) {
		string extension = fileName.substr(dotPos + (includeDot ? 0 : 1));
        std::for_each(extension.begin(), extension.end(), [](char &c) { c = ::tolower(c); });
        return extension;
	}
	return "";
}

#ifdef _WIN32

void searchFilesByType(const string &path, const string &type) {
    _finddata_t file;
    std::string filepath = path + "/*";
    intptr_t handle;

    if ( (int)(handle = _findfirst(filepath.c_str(), &file)) == -1 ) {
        return;
    }

    do {
        if (file.attrib & _A_SUBDIR) {
            std::string s = file.name;
            if (s == "." || s == "..")
                continue;

            std::string dirname = path + '/' + file.name;
            searchFilesByType(dirname, type);

        } else {
            if (getExtension(file.name, false).compare(type)==0) {
                std::string filename = path + '/' + file.name;
                files.push_back(filename);
            }
        }

    } while( _findnext(handle, &file) == 0 );

    _findclose(handle);
}

#else

void searchFilesByType(const string &path, const string &type) {
    DIR *p_dir;
    struct dirent *p_dirent;

    if((p_dir = opendir(path.c_str())) == NULL) {
        return;
    }

    while((p_dirent = readdir(p_dir))) {
        if (DT_REG == p_dirent->d_type) {
            // normal type file
            if (getExtension(p_dirent->d_name, false).compare(type)==0) {
                std::string filepath = path + '/' + p_dirent->d_name;
                files.push_back(filepath);
            }

        }else if (DT_DIR == p_dirent->d_type) {
            // directory
            std::string s = p_dirent->d_name;
            if (s == "." || s == "..")
                continue;
                
            std::string dirpath = path + '/' + p_dirent->d_name;
            searchFilesByType(dirpath, type);
        }
    }

    closedir(p_dir);
}

#endif

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

int main(int argc, char *argv[]) {
    CSimpleIniA config;

    // load from a data file
    SI_Error rc = config.LoadFile(CONFIG);
    if (rc != SI_OK) {
        cout << "loading " << CONFIG << " ERROR" << endl;
        return 1;
    }
    
    livetime = atoll(config.GetValue("TIME_OUT", "livetime"));

	CSimpleIniA::TNamesDepend pathes;
    config.GetAllValues("PATH", "path", pathes);

	CSimpleIniA::TNamesDepend types;
    config.GetAllValues("TYPE", "type", types);

	CSimpleIniA::TNamesDepend names;
    config.GetAllValues("NAME", "name", names);

	CSimpleIniA::TNamesDepend::const_iterator it0;
	CSimpleIniA::TNamesDepend::const_iterator it1;
    files.clear();
	for (it0 = pathes.begin(); it0 != pathes.end(); ++it0) {
		for (it1 = types.begin(); it1 != types.end(); ++it1) {
            searchFilesByType(it0->pItem, it1->pItem);
        }
	}
    sort(files.begin(), files.end());

    CSimpleIniA data;
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

    char s_tm[64];
    time_t now = time(NULL);
	for (it3 = names.begin(); it3 != names.end(); ++it3) {
        string filepath;
        time_t tm;
        updateData(filepath, tm, now, datas[it3->pItem]);
        data.SetValue(it3->pItem, "filepath", filepath.c_str());
        sprintf(s_tm, "%lld", tm);
        data.SetValue(it3->pItem, "tm", s_tm);

#if _WIN32
        SetEnvironmentVariable(it3->pItem, filepath.c_str());
#else
        setenv(it3->pItem, filepath.c_str(), 1);
#endif
    }
    rc = data.SaveFile(DATA);
    if (rc != SI_OK) {
        cout << "SAVING " << DATA << " ERROR" << endl;
        return 1;
    }

    return 0;
}