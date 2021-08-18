#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <tlhelp32.h>
#include <array>

#include "Converter.h"

class ProcessManager
{
public:
	ProcessManager(int, const std::vector<std::wstring>);

	int waitForPidToTerminate(void);
	int closeAllApps(void);

private:
	// functions
	int closeProcess(DWORD);
	int closeProcessesByName(const wchar_t*);
	std::vector<DWORD> getPidsByName(const wchar_t*);

	// fields
	int watchPid;
	std::vector<std::wstring> appsToClose;
};

