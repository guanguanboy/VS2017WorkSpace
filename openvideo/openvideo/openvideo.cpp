#include <thread>
#include "windows.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

VideoCapture g_cap2;
VideoCapture g_cap1;

void threadfun()
{
	//VideoCapture cap2(0);
	g_cap2.open(0);

	/*if (g_cap2.isOpened())
	{
		cout << "*** ***" << endl;
		cout << "摄像头2已启动！" << endl;
	}
	else
	{
		cout << "*** ***" << endl;
		cout << "警告：请检查摄像头2是否安装好!" << endl;
		cout << "程序结束！" << endl << "*** ***" << endl;
		return;
	}*/

	//bool isTwoOpened = cap2.isOpened();
	//namedWindow("cam2", CV_WINDOW_AUTOSIZE);


	//Mat frame2;

	//while (true)
	//{
	//	if (g_cap2.read(frame2))
	//	//if (!frame2.empty())
	//	{
	//		imshow("cam2", frame2);
	//		cvtColor(frame2, frame2, CV_RGB2GRAY);

	//	}

	//	if (waitKey(1) == 27)//按ESC键
	//	{
	//		break;
	//	}
	//}

	//g_cap2.release();
}


void threadfun1()
{
	//VideoCapture cap2(0);
	g_cap1.open(0);

	/*if (g_cap1.isOpened())
	{
		cout << "*** ***" << endl;
		cout << "摄像头2已启动！" << endl;
	}
	else
	{
		cout << "*** ***" << endl;
		cout << "警告：请检查摄像头2是否安装好!" << endl;
		cout << "程序结束！" << endl << "*** ***" << endl;
		return;
	}*/

	//bool isTwoOpened = cap2.isOpened();
	namedWindow("cam1", CV_WINDOW_AUTOSIZE);


	Mat frame2;

	while (true)
	{
		if (g_cap1.read(frame2))
			//if (!frame2.empty())
		{
			imshow("cam2", frame2);
			cvtColor(frame2, frame2, CV_RGB2GRAY);

		}

		if (waitKey(1) == 27)//按ESC键
		{
			break;
		}
	}

	g_cap1.release();
}

#if 0
int main(int argc, char** argv)
{
	namedWindow("OpenvideoDemo", WINDOW_AUTOSIZE);
	VideoCapture cap;
	//string videoName = string("../saveVideo/my_video.avi");
	cap.open("../saveVideo/depth.avi");
	Mat frame;

	int fps = cap.get(CV_CAP_PROP_FPS);

	printf("fps = %d\n", fps);

	if (cap.isOpened() == false)
	{
		return 0;
	}

	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}

		imshow("showVideo", frame);

		if (waitKey(33) >= 0)
		{
			break;
		}
	}

	return 0;
}
#endif


#if 0
int main()
{


	//VideoCapture cap1(1);
	//VideoCapture cap2(1);

	thread camera2Thread(threadfun);
	camera2Thread.detach();

	thread camera1Thread(threadfun1);
	camera1Thread.detach();

	while (true)
	{
		Sleep(500);
	}

	return 0;
}

#endif

#if 1

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap1;
	Sleep(500);
	VideoCapture cap2;

	bool stop(false);
	Mat frame1;
	Mat frame2;

	namedWindow("cam1", CV_WINDOW_AUTOSIZE);
	namedWindow("cam2", CV_WINDOW_AUTOSIZE);

	cap1.open(2);
	cap2.open(1);
	if (cap2.isOpened())
	{
		cout << "*** ***" << endl;
		cout << "摄像头已启动！" << endl;
	}
	else
	{
		cout << "*** ***" << endl;
		cout << "警告：请检查摄像头是否安装好!" << endl;
		cout << "程序结束！" << endl << "*** ***" << endl;
		return -1;
	}


	cap1.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	cap2.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap2.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	//cap1.set(CV_CAP_PROP_FOCUS, 0);
	//cap2.set(CV_CAP_PROP_FOCUS, 0);
	cap1.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	cap2.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));

	while (!stop)
	{
		if (cap1.read(frame1))
		{
			imshow("cam1", frame1);

			imwrite("frame1.bmp", frame1);

			//彩色帧转灰度
			cvtColor(frame1, frame1, CV_RGB2GRAY);
		}

		if (cap2.read(frame2))
		{
			imshow("cam2", frame2);
			imwrite("frame2.bmp", frame2);
			cvtColor(frame2, frame2, CV_RGB2GRAY);
		}

			if (waitKey(1) == 27)//按ESC键
			{
				stop = true;
				cout << "程序结束！" << endl;
				cout << "*** ***" << endl;
			}
		
	}
	return 0;
}

#endif

#if 0
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//【画框】
void Draw_rectangle(Mat img, Point pt1, Point pt2)
{
	rectangle(img, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
}

int main()
{
	Mat frame1, frame2, ROIImage1, ROIImage2, mask1, mask2, gray_Image1, gray_Image2;
	VideoCapture capture1(1);
	VideoCapture capture2(0);
	capture1.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	capture1.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	capture2.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	capture2.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if (!capture1.isOpened())
	{
		cout << "Come on baby 1 !" << endl;
		return -1;
	}
	if (!capture2.isOpened())
	{
		cout << "Come on baby 2 !" << endl;
		return -1;
	}
	Mat frame3(240, 640, CV_8UC3, Scalar(0, 0, 0));
	char temp_1[20];
	char temp_2[20];
	while (true)
	{
		capture1 >> frame1;
		capture2 >> frame2;
		Draw_rectangle(frame1, Point(0, 0), Point(frame1.cols, frame1.rows));
		Draw_rectangle(frame2, Point(0, 0), Point(frame2.cols, frame2.rows));
		//sprintf(temp_1, "capture1");
		//putText(frame1, temp_1, Point(frame1.cols / 16, frame1.rows / 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 255));
		//sprintf(temp_2, "capture2");
		//putText(frame2, temp_2, Point(frame2.cols / 16, frame2.rows / 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 255));
		ROIImage1 = frame3(Rect(0, 0, 320, 240));
		ROIImage2 = frame3(Rect(320, 0, 320, 240));
		//imshow("【ROIImage1】", ROIImage1);
		//imshow("【ROIImage2】", ROIImage2);
		cvtColor(frame1, gray_Image1, CV_RGB2GRAY);
		cvtColor(frame2, gray_Image2, CV_RGB2GRAY);
		mask1 = gray_Image1;
		mask2 = gray_Image2;
		frame1.copyTo(ROIImage1, mask1);
		frame2.copyTo(ROIImage2, mask2);
		imshow("【视频窗口一】", frame1);
		imshow("【视频窗口二】", frame2);
		imshow("【总窗口】", frame3);
		waitKey(1);
	}

	return 0;
}

#endif
