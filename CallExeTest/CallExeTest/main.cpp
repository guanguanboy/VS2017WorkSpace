#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>

int main()
{
	char ss[100];

	//sprintf(ss, "%s -o %s %s", "E:\\VS2017WorkSpace\\SimpleRead\\x64\\SimpleRead.exe", "c:\\txt\\aaa.txt.swf", "\"c:\\txt\\a a a.txt\"");
	snprintf(ss, 100, "%s", "DepthReaderPoll.exe");

	system(ss);

	//ShellExecute(NULL, "open", "calc.exe", "", "", SW_SHOW);

	//ShellExecute(NULL, "open", "notepad.exe", "c:\\MyLog.log", "", SW_SHOW);

	//ShellExecute(NULL, "open", "E:\\VS2017WorkSpace\\CallExeTest\\Debug\\DepthReaderPoll.exe", "", "", SW_SHOW);
	//ShellExecute(NULL, "open", "E:\\VS2017WorkSpace\\NiViewer\\x64\\Release\\NiViewer.exe", "", "", SW_SHOW);
	
	//���·��
	//ShellExecute(NULL, "open", "..\\Debug\\DepthReaderPoll.exe", "", "", SW_SHOW);
	
	//���·������DepthReaderPoll.exe ����CallExeTest.exe����Ŀ¼
	//ShellExecute(NULL, "open", "DepthReaderPoll.exe", "", "", SW_SHOW);

	return 0;
}