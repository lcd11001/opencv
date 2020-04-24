#include "C1_1_DisplayPicture.h"

using namespace cv;

int DisplayPicture(cv::String name)
{
	Mat img = imread(name);
	if (img.empty())
	{
		return -1;
	}
	const String windowName = "C1.1";

	namedWindow(windowName, WINDOW_AUTOSIZE);
	imshow(windowName, img);
	waitKey(0);
	destroyWindow(windowName);

	return 0;
}

int TestDisplayPicture()
{
	return DisplayPicture("../Assets/test.png");
}