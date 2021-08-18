#include "ProcessManager.h"

/// <summary>
/// Constructor
/// In: PID to watch
/// In: List of apps to close on exit
/// </summary>
/// <param name="pidToWatch"></param>
/// <param name="apps"></param>
ProcessManager::ProcessManager(int pidToWatch, const std::vector<std::wstring> apps)
	: watchPid(pidToWatch), appsToClose(apps) {}


/// <summary>
/// Waits on the PID, if valid, to close.
/// </summary>
/// <returns></returns>
int ProcessManager::waitForPidToTerminate() {
	if (watchPid <= 0) {
		// log
		return 0;
	}

	HANDLE handle = ::OpenProcess(SYNCHRONIZE, false, watchPid);
	if (handle == 0 || handle == INVALID_HANDLE_VALUE) {
		// log
		return 0;
	}

	// log

	::WaitForSingleObject(handle, INFINITE);
	return 1;
}

/// <summary>
/// Closes all the apps passed to constructor.
/// </summary>
/// <returns></returns>
int ProcessManager::closeAllApps() {
	// log

	for (auto app : appsToClose) {
		closeProcessesByName(app.c_str());
	}

	return 1;
}

/// <summary>
/// Close processes by name.
/// In: name of process
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
int ProcessManager::closeProcessesByName(const wchar_t* name) {
	std::vector<DWORD> pids = getPidsByName(name);
	for (auto pid : pids) {
		closeProcess(pid);
	}

	return 1;
}

/// <summary>
/// Close the process of PID given.
/// In: PID of process
/// </summary>
/// <param name="pid"></param>
/// <returns></returns>
int ProcessManager::closeProcess(DWORD pid) {
	HANDLE h = ::OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION, false, pid);

	// todo: make graceful exit
	// convert HANDLE to HWND
	// auto result = ::SendMessage(hwnd, WM_CLOSE, NULL, NULL);		// blocking
	// look into PostMessage(hwnd, WM_CLOSE, NULL, NULL);			// loop through getmodule to get title of window

	if (h != NULL && h != INVALID_HANDLE_VALUE) { 
		bool success = ::TerminateProcess(h, 0);
		// log
		::CloseHandle(h);
	}

	return 1;
}

/// <summary>
/// Gets the PID(s) by name given.
/// In: Name of process
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::vector<DWORD> ProcessManager::getPidsByName(const wchar_t* name) {
	// log

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	std::vector<DWORD> pids;

	if (Process32First(snapshot, &entry)) {
		do {
			if (!_wcsicmp(entry.szExeFile, name)) {
				pids.push_back(entry.th32ProcessID);
			}
		} while (Process32Next(snapshot, &entry));
	}

	if (snapshot != INVALID_HANDLE_VALUE)
		::CloseHandle(snapshot);

	// log

	return pids;
}
