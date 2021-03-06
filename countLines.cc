/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#ifdef WIN32
#include <windows.h>
#include <XGetopt.h>
#else
#include <unistd.h>
#endif
#include <stdint.h>
#include <iostream>
#include <vector>
#include <regex>
#include <codecvt>
#include <Directory.h>
#include <Counter.h>
#include <File.h>

static void PrintUsage()
{
    std::cout << "usage: countLines [-e regexp] [-d directory] [-t text]" << std::endl;
    std::cout << " -e: file regular expression pattern" << std::endl;
    std::cout << " -d: root processing directory" << std::endl;
    std::cout << " -t: text file dir. This text will be placed at the beginning of each" << std::endl;
    std::cout << "     file that matches regular expression" << std::endl;

    exit(0);
}

int32_t main(int32_t argc, char *argv[ ])
{
    std::wstring regex = L".*\\.(cc|cpp|h)";
    std::wstring dir = L".";
    std::wstring textFileDir = L"";

    int32_t c;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while ((c = getopt(argc, argv, "e:d:t:h")) != EOF)
        if(c == 'e')
            regex = converter.from_bytes(optarg);
        else if(c == 'd')
            dir = converter.from_bytes(optarg);
        else if(c == 't')
            textFileDir = converter.from_bytes(optarg);
        else if(c == '?' || c == 'h')
            PrintUsage();
        else {
            std::cout << "invalid option " << c << std::endl;
            PrintUsage();    
        }

    Counter::Counter counter;

    try{

        std::string text;

        if(textFileDir != L""){
            File::Data data = File::Read(textFileDir);
            std::for_each(data.begin(), data.end(), [&text](File::Data::value_type Value){text += Value;});
        }

        counter.Init(regex, dir, text);
        counter.Process();

    }catch(const std::regex_error &err){
        std::cout << "regex syntax error " << err.what();
        return 1;
    }catch(const Exception &err){
        std::wcout << L"processing error " << err.What();
        return 1;
    }

    std::cout << "lines count " << counter.GetLinesCount() << std::endl;
    return 0;
}