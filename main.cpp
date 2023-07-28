#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>
#include <wbemidl.h>
#define _WIN32_DCOM
#include <iostream>
using namespace std;
//#pragma comment(lib, "wbemuuid.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    HRESULT hr;
    hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
    { cout << "Failed to initialize COM library. Error code = 0x"
             << hex << hr << endl;
        return hr;
    }

    hr =  CoInitializeSecurity(
        NULL,                        // Security descriptor
        -1,                          // COM negotiates authentication service
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities of the client or server
        NULL);                       // Reserved

    if (FAILED(hr))
    {
        cout << "Failed to initialize security. Error code = 0x"
             << hex << hr << endl;
        CoUninitialize();
        return hr;                  // Program has failed.
    }


    IWbemLocator *pLoc = 0;

    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc);

    if (FAILED(hr))
    {
        cout << "Failed to create IWbemLocator object. Err code = 0x"
             << hex << hr << endl;
        CoUninitialize();
        return hr;     // Program has failed.
    }





    w.show();
    return a.exec();
}
