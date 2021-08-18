#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <codecvt>
#include <locale>

class Converter
{
public:
	static int strToInt(const std::string, int&);
	static const wchar_t* convertTo(const std::string);
	static const wchar_t* convertTo(const char*);
	static std::wstring strToWstr(char*);
};

