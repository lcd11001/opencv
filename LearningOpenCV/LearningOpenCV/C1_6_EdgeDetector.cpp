#include "C1_6_EdgeDetector.h"

using namespace cv;

int EdgeDetector(cv::String name)
{
	const String nameWindow1 = "Gray";
	const String nameWindow2 = "Canny";

	Mat img_rgb, img_gray, img_canny;
	Mat img_pyr1, img_pyr2;

	img_rgb = imread(name);
	if (img_rgb.empty())
	{
		return 1;
	}

	namedWindow(nameWindow1, WINDOW_AUTOSIZE);
	namedWindow(nameWindow2, WINDOW_AUTOSIZE);

	cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
	imshow(nameWindow1, img_gray);

	pyrDown(img_gray, img_pyr1);
	pyrDown(img_pyr1, img_pyr2);

	//Canny(img_gray, img_canny, 10, 100, 3, true);
	Canny(img_pyr2, img_canny, 10, 100, 3, true);
	imshow(nameWindow2, img_canny);

	waitKey(0);

	destroyWindow(nameWindow1);
	destroyWindow(nameWindow2);

	return 0;
}

int TestEdgeDetector()
{
	//return EdgeDetector("../Assets/test512.png");
	return EdgeDetector("../Assets/test.png");
}
