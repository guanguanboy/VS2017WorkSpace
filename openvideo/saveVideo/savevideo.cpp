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
	Mat src_img = imread("color_0.jpg");//imread()函数载入图像
									  //从文件中读入图像，注意图像路径最好不要用相对路径，因为CLion生成的exe不在当前目录下。
	if (src_img.empty())
	{
		fprintf(stderr, "Can not load image\n");//如果读入图像失败，返回错误信息
		return -1;
	}
	//显示图像
	imshow("origin image and rotate operation", src_img);//imshow()函数显示图像
	Mat des_img;
	flip(src_img, des_img, 0);//1代表水平方向旋转180度
							  //flip(src_img,des_img,0);//0代表垂直方向旋转180度
							  //flip(src_img,des_img,-1);//-1代表垂直和水平方向同时旋转
	imshow(" after rotate operation", des_img);//imshow()函数显示图像
	waitKey();

	system("pause");
	return 0;
}

#endif
