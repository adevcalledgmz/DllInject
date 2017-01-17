#include "inject.h"

#ifdef __cplusplus
extern "C" {
#endif

int Inject(DWORD procId, char* dllPath)
{
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
    if(handle)
    {
        LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandle((LPCWSTR)"kernel32.dll"), "LoadLibraryA"); //Cast to LPCWSTR is required only by Visual Studio.
        if(LoadLibAddr == NULL)
        {
            ERR("Cannot find LoadLibraryA Handle in kernel32.dll.");
            return -1;
        }

        LPVOID SpaceAlloc = (LPVOID)VirtualAllocEx(handle, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if(SpaceAlloc == NULL)
        {
            ERR("Cannot allocate enough memory for the specified dll path.");
            return -1;
        }

        if(!WriteProcessMemory(handle, (LPVOID)SpaceAlloc, dllPath, strlen(dllPath), NULL))
        {
            ERR("Cannot write the dll path into the remote process memory.");
            return -1;
        }

        if(CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibAddr, (LPVOID)SpaceAlloc, 0, 0) == NULL)
        {
            ERR("Cannot create a new thread into the remote process.");
            return -1;
        }

        CloseHandle(handle);
        VirtualFreeEx(handle, SpaceAlloc, strlen(dllPath), MEM_RELEASE);

        return 0;
    }

    ERR("Can't open remote process.");

    return -1;
}

#ifdef __cplusplus
}
#endif
