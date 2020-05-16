#include "C1_5_PyramidDown.h"

using namespace cv;

int PyramidDown(cv::String name)
{
	String nameWindow1 = "Example1";
	String nameWindow2 = "Example2";

	namedWindow(nameWindow1, WINDOW_AUTOSIZE);
	namedWindow(nameWindow2, WINDOW_AUTOSIZE);

	Mat img1, img2;
	img1 = imread(name);
	if (img1.empty())
	{
		return 1;
	}

	pyrDown(img1, img2);
	
	imshow(nameWindow1, img1);
	imshow(nameWindow2, img2);

	waitKey(0);

	destroyWindow(nameWindow1);
	destroyWindow(nameWindow2);

	return 0;
}

int TestPyramidDown()
{
	return PyramidDown("../Assets/test.png");
}