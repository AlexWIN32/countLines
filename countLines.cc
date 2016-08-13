#ifdef WIN32
#include <windows.h>
#include <XGetopt.h>
#else
#include <unistd.h>
#endif
#include <stdint.h>
#include <iostream>
#include <vector>
#include <Directory.h>

int32_t wmain( int32_t argc, wchar_t *argv[ ], wchar_t *envp[ ] )
{
    std::vector<std::wstring> files, dirs;

    Directory::Parse(L".", files, dirs);

    std::wcout << L"Files:" << std::endl;

    for(const std::wstring &file : files)
        std::wcout << file << std::endl;

    std::wcout << L"Dirs:" << std::endl;

    for(const std::wstring &dir : dirs)
        std::wcout << dir << std::endl;

    return 0;
}