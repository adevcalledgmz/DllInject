# DllInject
A simple dll injector written in c.

Documentation:
You're lucky, there is only one function :
int Inject(DWORD procId, char* dllPath)

Inject the dll dllPath into process who have id procId.

Be sure that dllPath is the COMPLETE path to the dll.
If no, use GetFullPathName.
