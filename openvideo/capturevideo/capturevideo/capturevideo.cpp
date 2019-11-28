#if 0
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

void detectFace(CascadeClassifier &faceDetector, const Mat &frame, Rect &rect);


int main(int argc, char ** argv)
{
	namedWindow("Capture", WINDOW_AUTOSIZE);

	VideoCapture cap;
	if (argc == 1)
	{
		cap.open(0);
	}
	else
	{
		cap.open(argv[1]);
	}

	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 960);

	if (!cap.isOpened())
	{
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	/* 加载Haar人脸检测器 */
	CascadeClassifier faceDetector;

	std::string faceDetectorModule = "haarcascade_frontalface_default.xml";


	//友好错误信息提示
	try {
		faceDetector.load(faceDetectorModule);
	}
	catch (cv::Exception e) {}
	if (faceDetector.empty())
	{
		std::cerr << "脸部检测器不能加载 (";
		std::cerr << faceDetectorModule << ")!" << std::endl;
		exit(1);
	}

	Mat frame;
	Rect faceRect;

	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}

		std::cout << "frame width =" << frame.cols << ", frame height =" << frame.rows << std::endl;

		int type = frame.type();
		std::cout << "frame type =" << type << std::endl;

		imshow("CaptureVideo", frame);

		detectFace(faceDetector, frame, faceRect);

		if (faceRect.height > 0 && faceRect.width > 0)
		{
			cv::rectangle(frame, faceRect, cv::Scalar(0, 255, 0), 4, 8, 0);

		}

		imshow("Detected faces", frame);
		if (waitKey(33) >= 0)
		{
			//break;
		}
	}
}

void Pic2Gray(Mat camerFrame, Mat &gray)
{
	//普通台式机3通道BGR,移动设备为4通道
	if (camerFrame.channels() == 3)
	{
		cvtColor(camerFrame, gray, CV_BGR2GRAY);
	}
	else if (camerFrame.channels() == 4)
	{
		cvtColor(camerFrame, gray, CV_BGRA2GRAY);
	}
	else
		gray = camerFrame;
}


void detectFace(CascadeClassifier &faceDetector, const Mat &frame, Rect &rect)
{
	Mat gray;
	Pic2Gray(frame, gray);

	//直方图均匀化(改善图像的对比度和亮度)
	Mat equalizedImg;
	equalizeHist(gray, equalizedImg);

	//人脸检测用Cascade Classifier::detectMultiScale来进行人脸检测

	int flags = CASCADE_FIND_BIGGEST_OBJECT | CASCADE_DO_ROUGH_SEARCH;	//只检测脸最大的人
																		//int flags = CASCADE_SCALE_IMAGE;	//检测多个人
	Size minFeatureSize(30, 30);
	float searchScaleFactor = 1.1f;
	int minNeighbors = 4;
	std::vector<Rect> faces;
	faceDetector.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

	int facenum = faces.size();

	//找最大的脸
	int maxFaceIndex = 0;
	for (int i = 1; i < facenum; i++)
	{
		if (faces[i].width > faces[maxFaceIndex].width)
		{
			maxFaceIndex = i;
		}
	}

	if (facenum > 0)
	{
			rect = faces[maxFaceIndex];
	}
	else
	{
		rect.width = 0;
		rect.height = 0;
	}


	return;
}

#endif
#include "windows.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap1(2);
	Sleep(500);
	//VideoCapture cap2(1);

	bool stop(false);
	Mat frame1;
	Mat frame2;

	namedWindow("cam1", CV_WINDOW_AUTOSIZE);
	//namedWindow("cam2", CV_WINDOW_AUTOSIZE);

	if (cap1.isOpened())
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

	//cap1.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	//cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//cap2.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	//cap2.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//cap1.set(CV_CAP_PROP_FOCUS, 0);
	//cap2.set(CV_CAP_PROP_FOCUS, 0);
	//cap1.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	//cap2.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));

	while (!stop)
	{
		if (cap1.read(frame1))
		{
			imshow("cam1", frame1);

			imwrite("frame1.bmp", frame1);

			//彩色帧转灰度
			cvtColor(frame1, frame1, CV_RGB2GRAY);
		}

		/*if (cap2.read(frame2))
		{
			imshow("cam2", frame2);
			imwrite("frame2.bmp", frame2);
			cvtColor(frame2, frame2, CV_RGB2GRAY);
		}*/

		if (waitKey(1) == 27)//按ESC键
		{
			stop = true;
			cout << "程序结束！" << endl;
			cout << "*** ***" << endl;
		}

	}
	return 0;
}