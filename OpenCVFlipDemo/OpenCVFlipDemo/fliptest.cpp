#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#if 0
void main() {


cv::Mat image = cv::imread("ir_0.png", cv::IMREAD_UNCHANGED);

cv::Mat image_fliped;
cv::flip(image, image_fliped, 1);

//cv::imshow("lenna", image);
//cv::imshow("fliped lenna", image_fliped);

cv::imwrite("flipped_ir.png", image_fliped);

cv::waitKey(0);
return;

}

#endif

/*
	如下演示将图像顺时针旋转90度
*/
void main() {


	cv::Mat image = cv::imread("color_0.jpg", cv::IMREAD_UNCHANGED);

	cv::Mat image_rotated;
	cv::rotate(image, image_rotated, cv::ROTATE_90_CLOCKWISE);

	cv::imshow("lenna", image);
	cv::imshow("fliped lenna", image_rotated);

	cv::imwrite("rotated_color.png", image_rotated);

	cv::waitKey(0);
	return;

}