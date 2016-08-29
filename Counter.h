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
    int64_t linesCnt = 0;
    void ProcessDir(const std::wstring &Path);
    void ProcessFile(const std::wstring &Path);
public:
    int64_t GetLinesCount() const {return linesCnt;}
    void Init(const std::wstring &Regex, const std::wstring &Dir);
    void Process();
};

}