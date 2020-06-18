/*
������ ��OpenCV��̬���ڲ����ر���õ�һ�ֹ��ߣ��������ڴ��ڶ����ڡ�

����OpenCV�в�û��ʵ�ְ�ť�Ĺ��ܣ����Ժܶ�ʱ�����ǻ������ý���0-1�Ļ��������ǰ���ť�İ���
������Ч����
*/
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace  cv;

#define WINDOW_NAME "���Ի��ʾ��"

const int g_nMaxAlphaValue = 100; //Alphaֵ�����ֵ
int g_nAlphaValueSlider; //��������Ӧ�ı���
double g_dAlphaValue;
double g_dBetaValue;

//�����洢ͼ��ı���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*)
{
	//�����ǰalphaֵ��������ֵ�ı���
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

	//���û�������ʼֵΪ70
	g_nAlphaValueSlider = 70;

	//��������
	namedWindow(WINDOW_NAME, 1);

	//�ڴ����Ĵ������½�һ��������
	char TrackbarName[50];
	sprintf(TrackbarName, "alpha value = %d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	//����ڻص���������ʾ
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);

	return 0;
}