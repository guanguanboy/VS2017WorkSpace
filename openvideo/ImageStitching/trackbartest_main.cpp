/*
滑动条 是OpenCV动态调节参数特别好用的一种工具，它依附于窗口而存在。

由于OpenCV中并没有实现按钮的功能，所以很多时候，我们还可以用仅含0-1的滑动条来是俺按钮的按下
、弹起效果。
*/
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace  cv;

#define WINDOW_NAME "线性混合示例"

const int g_nMaxAlphaValue = 100; //Alpha值得最大值
int g_nAlphaValueSlider; //滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*)
{
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue = (double)(g_nAlphaValueSlider / g_nMaxAlphaValue);

	g_dBetaValue = 1.0 - g_dAlphaValue;

	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	imshow(WINDOW_NAME, g_dstImage);

	return;
}

int main(int argc, char** argv)
{
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");

	if (!g_srcImage1.data)
	{
		printf("read image1 failed.\n");
		return -1;
	}

	if (!g_srcImage2.data)
	{
		printf("read image2 failed.\n");
		return -1;
	}

	//设置滑动条初始值为70
	g_nAlphaValueSlider = 70;

	//创建窗体
	namedWindow(WINDOW_NAME, 1);

	//在创建的窗体中新建一个滑动条
	char TrackbarName[50];
	sprintf(TrackbarName, "alpha value = %d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	//结果在回调函数中显示
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);

	return 0;
}