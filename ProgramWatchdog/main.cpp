#include "ProcessManager.h"
#include "Converter.h"

#include <fstream>

const std::vector<std::wstring> APPS = {
	// any applications that the watchdog will close
	// L"<program>.exe"
};

/// <summary>
/// Main entry point.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Missing PID, exiting: " << argv[0] << std::endl;
		return 1;
	}

	int pid = 0;
	if (!Converter::strToInt(argv[1], pid) || pid <= 0) {
		std::cout << "Invalid PID: " << pid << std::endl;
		return 1;
	}

	int logLevel = 2;
	if (!Converter::strToInt(argv[2], logLevel)) {
		std::cout << "Invalid log level: " << pid << std::endl;
		return 1;
	}

	int numDaysRetainLogs = 30;
	if (!Converter::strToInt(argv[3], numDaysRetainLogs)) {
		std::cout << "Invalid number of days to retain log files: " << pid << std::endl;
		return 1;
	}

	std::wstring defPath = Converter::strToWstr(argv[0]);
	// initialize logging

	std::cout << "Waiting on PID: " << pid << std::endl;

	ProcessManager pm(pid, APPS);
	pm.waitForPidToTerminate();

	std::cout << pid << " terminated, closing all processes..." << std::endl;
	pm.closeAllApps();

	// final logging

	return 0;
}
