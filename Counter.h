/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#pragma once
#include <regex>
#include <stdint.h>

namespace Counter
{

class Counter
{
private:
    std::wregex regex;
    std::wstring dir;
    std::string text;
    int64_t linesCnt = 0;
    void ProcessDir(const std::wstring &Path);
    void ProcessFile(const std::wstring &Path);
public:
    int64_t GetLinesCount() const {return linesCnt;}
    void Init(const std::wstring &Regex,
              const std::wstring &Dir,
              const std::string &Text);
    void Process();
};

}