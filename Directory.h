#pragma once
#include <Exception.h>
#include <vector>
#include <string>

namespace Directory
{

void Parse(const std::wstring &Path, std::vector<std::wstring> &Files, std::vector<std::wstring> &Dirs);

}
