#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

extern "C" {
#include "internal_types.h"
#include "connectome.h"
#define export __declspec(dllexport)
}

using namespace std;

string GetLibraryPath(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved) {

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

	string path = GetLibraryPath(hModule);

	const char *modulePath;

	modulePath = path.c_str();
	
	//initialize(modulePath);

    return TRUE;
}

string GetLibraryPath(HMODULE hModule) {
	const int bufferSize = 1000;

	LPTSTR dllFullPath = new TCHAR[bufferSize];

	GetModuleFileName(hModule, dllFullPath, bufferSize);

	wstring w = dllFullPath;
	string path_string = string(w.begin(), w.end());

	delete[] dllFullPath;

	return path_string;
}
