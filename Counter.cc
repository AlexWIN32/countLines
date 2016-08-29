#include <Counter.h>
#include <Exception.h>
#include <Directory.h>
#include <fstream>
#include <iostream>

namespace Counter
{

void Counter::Init(const std::wstring &Regex, const std::wstring &Dir)
{
    regex = std::wregex(Regex);
    dir = Dir;
}

void Counter::Process()
{
    linesCnt = 0;
    ProcessDir(dir);
}

void Counter::ProcessFile(const std::wstring &Path)
{
    std::wcout << L"processing " << Path << L"... ";

    int32_t linesInFile = 0;

    std::ifstream file(Path);

    std::string line;
    while (std::getline(file, line))
        linesInFile++;

    std::wcout << linesInFile << L" lines." << std::endl;

    linesCnt += linesInFile;
}

void Counter::ProcessDir(const std::wstring &Path)
{
    std::vector<std::wstring> files, dirs;

    Directory::Parse(Path, files, dirs);

    for(const std::wstring &file : files)
        if(std::regex_match(file, regex))
            ProcessFile(Path + L"/" + file);

    for(const std::wstring &dir : dirs)
        ProcessDir(Path + L"/" + dir);
}

}