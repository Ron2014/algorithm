#define _AFXDLL
#include <afxwin.h>
#include <iostream>
#include <tchar.h>  
#include <afx.h>
#include <afxpriv.h>
using namespace std;

#include "upenv.h"

#define MAX_LEN 256
#define ENV_VAR_PATH "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"

void setEnvVar(const char *key, const char *value)
{
    HKEY hkResult;  //键的句柄
    LPCTSTR environmentKey =_T(ENV_VAR_PATH);

    if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, environmentKey , 0, KEY_SET_VALUE | KEY_READ , &hkResult)) //打开键environment
    {         
        MessageBox(NULL, _T("访问注册表出错！\n请使用管理员帐户执行本程序！"), _T("ERROR"), MB_ICONERROR); 
        return;
    }

    long setResult = RegSetValueEx(hkResult, key, 0, /*REG_SZ*/REG_EXPAND_SZ, (LPBYTE)value, _tcsclen(value)*sizeof(TCHAR));//设置某子键下特定名称的值。  
    if(ERROR_SUCCESS != setResult) cout << "set env " << key << ":" << value << " error!" << endl;
 
    DWORD dwResult;
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE , 0, LPARAM(_T("Environment")), SMTO_ABORTIFHUNG, 5000, &dwResult);//广播立即执行  
    if(ERROR_SUCCESS != dwResult) cout << "set env " << key << ":" << value << " error!" << endl;

    RegCloseKey(hkResult);//释放键句柄 
}