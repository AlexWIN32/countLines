/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#include <Directory.h>
#ifdef WIN32
#include <windows.h>
#endif

namespace Directory
{

void Parse(const std::wstring &Path, std::vector<std::wstring> &Files, std::vector<std::wstring> &Dirs)
{
#ifdef WIN32

    WIN32_FIND_DATAW data;

    HANDLE h = FindFirstFileW(std::wstring(Path + L"\\*").c_str(), &data);

    if(h == INVALID_HANDLE_VALUE)
        throw IOException(L"cant open " + Path);

    do{
        std::wstring name = data.cFileName;

        if(name == L"." || name == L"..")
            continue;

        DWORD attrs = GetFileAttributesW((Path + L"\\" + name).c_str());
        if(attrs == INVALID_FILE_ATTRIBUTES)
            throw IOException(L"cant get attributes for " + name);

        (attrs & FILE_ATTRIBUTE_DIRECTORY ? Dirs : Files).push_back(name);

    }while(FindNextFileW(h, &data) != 0);

    FindClose(h);

#endif
}

}