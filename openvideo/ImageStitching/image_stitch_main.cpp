#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching.hpp>

using namespace std;
using namespace cv;

//hconcat �������ͷ�ļ���#include <opencv2/core.hpp>
void ImageStitching(vector<Mat> imageVector, Mat &outputImage, int rowImageCount_, int imageWidth_, int imageHeight_)
{
	vector<Mat> imageVec;  //��Ŵ�����ϲ���ͼƬ
	vector<Mat> hImageVec; //�������ϲ��Ľ��ͼ

	for (int i = 0; i < imageVector.size(); i++)
	{
		//����ϲ�
		if ((i + 1) % rowImageCount_ == 0) //����0��ʾ ͼƬ�����Ѿ��㹻��Ҫ���γ�һ����
		{
			Mat combine(imageHeight_, imageWidth_, CV_8UC3); //ÿһ�кϲ��Ľ��ͼ
			imageVec.push_back(imageVector.at(i));
			hconcat(imageVec, combine); //����ϲ�
			hImageVec.push_back(combine);
			imageVec.clear(); //��գ����������һ��ͼƬ
		}
		else
		{
			imageVec.push_back(imageVector.at(i));
		}
	}

	//������ϲ����ͼ������ϳ�һ��ͼ
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
		const int rowImageCount = 3; //��ʾ����ͼƬ�ϳ�һ��

		Mat outputimage(imageHeight * 2, imageWidth * 3, CV_8UC3);

		ImageStitching(inputIamgeVector, outputimage, rowImageCount, imageWidth, imageHeight);
		Mat resizedOutputImg;

		resize(outputimage, resizedOutputImg, Size(imageWidth, imageHeight));
		//namedWindow("ƴ�Ӻ��ͼ");
		//imshow("ƴ�Ӻ��ͼ", outputimage);
		imshow("ƴ�Ӳ���С���ͼ", resizedOutputImg);
		waitKey(5000);
	}

	return 0;
}

#endif


