/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#include <Counter.h>
#include <Exception.h>
#include <Directory.h>
#include <fstream>
#include <iostream>
#include <File.h>

namespace Counter
{

void Counter::Init(const std::wstring &Regex, const std::wstring &Dir, const std::string &Text)
{
    regex = std::wregex(Regex);
    dir = Dir;
    text = Text;
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

    std::wcout << linesInFile << L" lines. ";

    file.close();

    if(text != ""){
        File::Data content = File::Read(Path);

        content.insert(content.begin(), text.begin(), text.end());

        File::Rewrite(Path, content);

        std::wcout << " custom text added. ";
    }
    
    std::wcout << std::endl;

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