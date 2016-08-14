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

int32_t main(int32_t argc, char *argv[ ])
{
    std::wstring regex = L".*\\.(cc|cpp|h)";
    std::wstring dir = L".";

    int32_t c;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while ((c = getopt(argc, argv, "e:d:h")) != EOF)
        if(c == 'e')
            regex = converter.from_bytes(optarg);
        else if(c == 'd')
            dir = converter.from_bytes(optarg);
        else if(c == 'd' || c == 'h'){
            std::cout << "usage: countLines [-e regexp] [-d directory]" << std::endl;
            std::cout << " -e: file regular expression pattern" << std::endl;
            std::cout << " -d: root processing directory" << std::endl;
        }

    Counter::Counter counter;

    try{

        counter.Init(regex, dir);
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