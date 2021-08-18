#include "Converter.h"

/// <summary>
/// Converts a std::string to an int
/// In: string to convert
/// In: reference to result
/// </summary>
/// <param name="s"></param>
/// <param name="outInt"></param>
/// <returns>Greater than 0 for success, else unsuccessful.</returns>
int Converter::strToInt(const std::string s, int &outInt) {
	try {
		std::string::size_type sz;
		outInt = std::stoi(s, &sz);
		return 1;
	}
	catch (std::invalid_argument const& ex) {
		// log
	}
	catch (std::out_of_range const& ex) {
		// log
	}

	return 0;
}

/// <summary>
/// Converts a string to a wchar_t*
/// In: string to convert
/// </summary>
/// <param name="toConvert"></param>
/// <returns></returns>
const wchar_t* Converter::convertTo(const std::string toConvert) {
	try {
		std::wstring ws(toConvert.begin(), toConvert.end());
		const wchar_t* wct = ws.c_str();
		return wct;
	} 
	catch (std::exception const& ex) {
		return nullptr;
	}
}

/// <summary>
/// Converts a char* to a wchar_t*
/// In: char* to convert
/// </summary>
/// <param name="toConvert"></param>
/// <returns></returns>
const wchar_t* Converter::convertTo(const char* toConvert) {
	try {
		const size_t size = strlen(toConvert) + 1;
		wchar_t* w = new wchar_t[size];
		size_t outSize;
		mbstowcs_s(&outSize, w, size, toConvert, size - 1);
		return w;
	} 
	catch (std::exception const& ex) {
		return nullptr;
	}
}

/// <summary>
/// Converts a string to a wstring.
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
std::wstring Converter::strToWstr(char* s) {
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(s);
}