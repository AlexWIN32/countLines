#include <File.h>
#include <limits>
#ifndef WIN32
#include <codecvt>
#endif
#include <stdint.h>

#if defined(_MSC_VER) && (_MSC_VER == 1800)
#define noexcept throw()
#endif

namespace File
{

class Guard
{
private:
    FILE *file = NULL;
public:
    Guard(const Guard&) = delete;
    Guard &operator=(const Guard&) = delete;
    Guard(FILE *File) : file(File){}
    FILE *Get() const noexcept {return file;}
    ~Guard(){fclose(file);}
};

static FILE * Open(const std::wstring &Path, const std::wstring &&Mode)
{
    FILE *outFile;

#ifdef WIN32
    if(_wfopen_s(&outFile, Path.c_str(), Mode.c_str()))
        throw IOException(L"Fail to open" + Path);
#else 
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    if(fopen(converter.to_bytes(Path),"r"))
        throw IOException(L"Fail to open" + Path);
#endif

    return outFile;
}

Data&& Read(const std::wstring &Path)
{
    File::Guard file = Open(Path, L"rb");

    fseek(file.Get(), 0, SEEK_END);

    int64_t size = ftell(file.Get());

    fseek(file.Get(), 0, SEEK_SET);

    if(size > std::numeric_limits<Data::size_type>::max())
        throw IOException(L"File is too big");

    Data data(size);

    size_t rSize = fread(&data[0], sizeof(Data::value_type), size, file.Get());
    if(rSize != size)
        throw IOException(L"Cant read from file");

    return std::move(data);
}

void Rewrite(const std::wstring &Path, const Data &FileData)
{
    File::Guard file = Open(Path, L"w");

    if(fwrite(&FileData[0], sizeof(Data::size_type), FileData.size(), file.Get()))
        throw IOException(L"Cant read from file");
}

}