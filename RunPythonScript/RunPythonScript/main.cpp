#include <stdlib.h>
#include <string>

int main()
{
	//std::string python_script_pth = "python D://Code2020//BodyMeasurementAlg//test_body_recon.py";

	std::string python_script_pth = "python E:\\VS2017WorkSpace\\RunPythonScript\\x64\\Debug\\test_body_recon.py";

	system(python_script_pth.c_str());

	system("pause"); //system会阻塞直到执行结束
	return 0;
}
