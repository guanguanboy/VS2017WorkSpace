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

