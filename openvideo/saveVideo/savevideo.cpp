#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

#if 1
int main(int argc, char* argv[])
{
	namedWindow("Example2_11", WINDOW_AUTOSIZE);

	namedWindow("logpolar", WINDOW_AUTOSIZE);

	VideoCapture capture;

	capture.open(0);

	if (capture.isOpened() == false)
	{
		return 0;
	}

	//double fps = capture.get(CAP_PROP_FPS);

	Size size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter writer;

	try
	{
		writer.open("my_video.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, size);
	}
	catch (cv::Exception e)
	{
		std::cout << e.msg << std::endl;
	}
	Mat log_polarFrame, bgr_frame;

	while (true)
	{
		capture >> bgr_frame;
		if (bgr_frame.empty())
		{
			break;
		}

		imshow("Example2_11", bgr_frame);

		logPolar(bgr_frame, log_polarFrame, Point2f(bgr_frame.cols / 2, bgr_frame.rows / 2), 40, WARP_FILL_OUTLIERS);

		imshow("logpolar", log_polarFrame);

		writer << log_polarFrame;

		char c = waitKey(10);

		if (c == 27)
		{
			break;
		}

	}

	capture.release();

	return 0;
}

#endif

#if 0
int main()
{
	Mat src_img = imread("color_0.jpg");//imread()��������ͼ��
									  //���ļ��ж���ͼ��ע��ͼ��·����ò�Ҫ�����·������ΪCLion���ɵ�exe���ڵ�ǰĿ¼�¡�
	if (src_img.empty())
	{
		fprintf(stderr, "Can not load image\n");//�������ͼ��ʧ�ܣ����ش�����Ϣ
		return -1;
	}
	//��ʾͼ��
	imshow("origin image and rotate operation", src_img);//imshow()������ʾͼ��
	Mat des_img;
	flip(src_img, des_img, 0);//1����ˮƽ������ת180��
							  //flip(src_img,des_img,0);//0����ֱ������ת180��
							  //flip(src_img,des_img,-1);//-1����ֱ��ˮƽ����ͬʱ��ת
	imshow(" after rotate operation", des_img);//imshow()������ʾͼ��
	waitKey();

	system("pause");
	return 0;
}

#endif
