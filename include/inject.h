#ifndef INJECT_H_INCLUDED
#define INJECT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#define ERR(msg) MessageBoxA(NULL, msg, "Error", MB_ICONERROR)

int Inject(DWORD procId, char* dllPath);

#ifdef __cplusplus
}
#endif

#endif
