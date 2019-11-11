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

