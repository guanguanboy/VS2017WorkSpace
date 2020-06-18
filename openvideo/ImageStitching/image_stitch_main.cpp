#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching.hpp>

using namespace std;
using namespace cv;

//hconcat 这个函数头文件是#include <opencv2/core.hpp>
void ImageStitching(vector<Mat> imageVector, Mat &outputImage, int rowImageCount_, int imageWidth_, int imageHeight_)
{
	vector<Mat> imageVec;  //存放待横向合并的图片
	vector<Mat> hImageVec; //存放纵向合并的结果图

	for (int i = 0; i < imageVector.size(); i++)
	{
		//横向合并
		if ((i + 1) % rowImageCount_ == 0) //等于0表示 图片数量已经足够按要求形成一行了
		{
			Mat combine(imageHeight_, imageWidth_, CV_8UC3); //每一行合并的结果图
			imageVec.push_back(imageVector.at(i));
			hconcat(imageVec, combine); //横向合并
			hImageVec.push_back(combine);
			imageVec.clear(); //清空，继续添加下一行图片
		}
		else
		{
			imageVec.push_back(imageVector.at(i));
		}
	}

	//将横向合并后的图像竖向合成一张图
	vconcat(hImageVec, outputImage);
}

#if 0
int main()
{
	Mat img1, img2, img3, img4, img5, img0;
	vector<Mat> inputIamgeVector;
	img0 = imread("color_0.jpg");
	img1 = imread("color_1.jpg");
	img2 = imread("color_2.jpg");
	img3 = imread("color_3.jpg");
	img4 = imread("color_4.jpg");
	img5 = imread("color_5.jpg");
	//cv::resize();
	if (!img1.empty() && !img2.empty() && !img3.empty() && !img3.empty() && !img4.empty() && !img5.empty() && !img0.empty())
	{
		inputIamgeVector.push_back(img1);
		inputIamgeVector.push_back(img2);
		inputIamgeVector.push_back(img3);
		inputIamgeVector.push_back(img4);
		inputIamgeVector.push_back(img5);
		inputIamgeVector.push_back(img0);

		const int imageWidth = img1.cols;
		const int imageHeight = img1.rows;
		const int rowImageCount = 3; //表示三张图片合成一行

		Mat outputimage(imageHeight * 2, imageWidth * 3, CV_8UC3);

		ImageStitching(inputIamgeVector, outputimage, rowImageCount, imageWidth, imageHeight);
		Mat resizedOutputImg;

		resize(outputimage, resizedOutputImg, Size(imageWidth, imageHeight));
		//namedWindow("拼接后的图");
		//imshow("拼接后的图", outputimage);
		imshow("拼接并缩小后的图", resizedOutputImg);
		waitKey(5000);
	}

	return 0;
}

#endif


