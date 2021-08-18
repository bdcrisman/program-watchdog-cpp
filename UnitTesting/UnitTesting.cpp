#include "pch.h"
#include "CppUnitTest.h"

// included the cpp files due to linker err
#include "../ProgramWatchdog/ProcessManager.h"
#include "../ProgramWatchdog/ProcessManager.cpp"
#include "../ProgramWatchdog/Converter.h"
#include "../ProgramWatchdog/Converter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTesting)
	{
	public:

#pragma region ProcessManager
		const std::vector<std::string> APPS = { "Calculator.exe" };
		const DWORD PID = 8704;

		TEST_METHOD(Test_GetPidByName)
		{
			ProcessManager p(PID, APPS);

			DWORD pid = 0;
			p.getPidByName("Calculator.exe", pid);
			Assert::IsTrue(pid == PID);
		}

		TEST_METHOD(Test_CloseProcess)
		{
			ProcessManager p(PID, APPS);
			auto result = p.closeProcess(13964);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(Test_GetPidsByName)
		{
			ProcessManager p(PID, APPS);
			auto result = p.getPidsByName("Calculator.exe");
			Assert::IsTrue(result.size() == 1);
		}

		TEST_METHOD(Test_CloseProcessByName)
		{
			ProcessManager p(PID, APPS);
			auto result = p.closeProcessByName("Calculator.exe");
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(Test_CloseProcessesByName)
		{
			ProcessManager p(PID, APPS);
			auto result = p.closeProcessesByName("Calculator.exe");
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(Test_CloseAllApps)
		{
			ProcessManager p(PID, APPS);
			auto result = p.closeAllApps();
			Assert::IsTrue(result == 1);
		}
#pragma endregion ProcessManager

#pragma region Converter
		TEST_METHOD(Test_ConvertStringToInt_Equal)
		{
			int result = 0;
			std::string s = "12";
			Converter::strToInt(s, result);
			Assert::AreEqual(12, result);
		}

		TEST_METHOD(Test_ConvertStringToInt_NotEqual)
		{
			int result = 0;
			std::string s = "12";
			Converter::strToInt(s, result);
			Assert::AreNotEqual(13, result);
		}

		TEST_METHOD(Test_ConvertStringWchart_Equal)
		{
			std::string s = "TTSServiceIPC.exe";
			const wchar_t* result = Converter::convertTo(s);
			Assert::IsTrue(result != nullptr);
		}

		TEST_METHOD(Test_ConvertCharWchart)
		{
			char* s = "0x14";
			const wchar_t* result = Converter::convertTo(s);
			Assert::IsTrue(result != nullptr);
		}
#pragma endregion Converter
	};
}
