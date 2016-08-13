#pragma once 
#include <string>

class Exception
{
private:
    std::wstring msg;
public:
    Exception(const std::wstring &Msg) : msg(Msg) {}
    const std::wstring &What() const {return msg;}
};

#define DECLARE_EXCEPTION(CLASS_NAME) struct CLASS_NAME : public Exception{CLASS_NAME(const std::wstring &Msg) : Exception(Msg){}};
#define DECLARE_CHILD_EXCEPTION(CLASS_NAME, BASE_CLASS_NAME) struct CLASS_NAME : public BASE_CLASS_NAME{CLASS_NAME(const std::wstring &Msg) : BASE_CLASS_NAME(Msg){}};

DECLARE_EXCEPTION(IOException);