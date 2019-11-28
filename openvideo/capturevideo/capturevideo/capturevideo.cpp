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

	/* ����Haar��������� */
	CascadeClassifier faceDetector;

	std::string faceDetectorModule = "haarcascade_frontalface_default.xml";


	//�Ѻô�����Ϣ��ʾ
	try {
		faceDetector.load(faceDetectorModule);
	}
	catch (cv::Exception e) {}
	if (faceDetector.empty())
	{
		std::cerr << "������������ܼ��� (";
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
	//��̨ͨʽ��3ͨ��BGR,�ƶ��豸Ϊ4ͨ��
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

	//ֱ��ͼ���Ȼ�(����ͼ��ĶԱȶȺ�����)
	Mat equalizedImg;
	equalizeHist(gray, equalizedImg);

	//���������Cascade Classifier::detectMultiScale�������������

	int flags = CASCADE_FIND_BIGGEST_OBJECT | CASCADE_DO_ROUGH_SEARCH;	//ֻ�����������
																		//int flags = CASCADE_SCALE_IMAGE;	//�������
	Size minFeatureSize(30, 30);
	float searchScaleFactor = 1.1f;
	int minNeighbors = 4;
	std::vector<Rect> faces;
	faceDetector.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

	int facenum = faces.size();

	//��������
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
		cout << "����ͷ��������" << endl;
	}
	else
	{
		cout << "*** ***" << endl;
		cout << "���棺��������ͷ�Ƿ�װ��!" << endl;
		cout << "���������" << endl << "*** ***" << endl;
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

			//��ɫ֡ת�Ҷ�
			cvtColor(frame1, frame1, CV_RGB2GRAY);
		}

		/*if (cap2.read(frame2))
		{
			imshow("cam2", frame2);
			imwrite("frame2.bmp", frame2);
			cvtColor(frame2, frame2, CV_RGB2GRAY);
		}*/

		if (waitKey(1) == 27)//��ESC��
		{
			stop = true;
			cout << "���������" << endl;
			cout << "*** ***" << endl;
		}

	}
	return 0;
}