#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <iostream>

using namespace std;

#if 0
int main()
{
	char ss[100];

	//sprintf(ss, "%s -o %s %s", "E:\\VS2017WorkSpace\\SimpleRead\\x64\\SimpleRead.exe", "c:\\txt\\aaa.txt.swf", "\"c:\\txt\\a a a.txt\"");
	//snprintf(ss, 100, "%s", "DepthReaderPoll.exe");

	//system(ss);

	HINSTANCE hinstance = ShellExecute(NULL, "open", "calc.exe", "", "", SW_SHOW);

	WaitForSingleObject(hinstance, 200000);
	//ShellExecute(NULL, "open", "notepad.exe", "c:\\MyLog.log", "", SW_SHOW);

	//ShellExecute(NULL, "open", "E:\\VS2017WorkSpace\\CallExeTest\\Debug\\DepthReaderPoll.exe", "", "", SW_SHOW);
	//ShellExecute(NULL, "open", "E:\\VS2017WorkSpace\\NiViewer\\x64\\Release\\NiViewer.exe", "", "", SW_SHOW);
	
	//相对路径
	//ShellExecute(NULL, "open", "..\\Debug\\DepthReaderPoll.exe", "", "", SW_SHOW);
	
	//相对路径，将DepthReaderPoll.exe 放在CallExeTest.exe所在目录
	//ShellExecute(NULL, "open", "DepthReaderPoll.exe", "", "", SW_SHOW);

	return 0;
}

#endif

//使用createprocess的方式,可以等待
int main()
{

	//SHELLEXECUTEINFO ShExecInfo = { 0 };
	//ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	//ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	//ShExecInfo.hwnd = NULL;
	//ShExecInfo.lpVerb = NULL;
	//ShExecInfo.lpFile = "E:\\VS2017WorkSpace\\CallExeTest\\Debug\\DepthReaderPoll.exe";
	//ShExecInfo.lpParameters = "";
	//ShExecInfo.lpDirectory = NULL;
	//ShExecInfo.nShow = SW_SHOW;
	//ShExecInfo.hInstApp = NULL;
	//ShellExecuteEx(&ShExecInfo);
	//WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field
	if (CreateProcess("E:\\VS2017WorkSpace\\CallExeTest\\Debug\\DepthReaderPoll.exe", NULL,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo))
	{
		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

		DWORD dwExitCode;
		if (GetExitCodeProcess(ProcessInfo.hProcess, &dwExitCode))
		{
			cout << dwExitCode << endl;
			if (dwExitCode == 0)
			{
				cout << "sucess" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}
		}

		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);
	}
	else
	{
		printf("The process could not be started...");
	}

	return 0;
}