#include "C1_2_DisplayVideo.h"

using namespace cv;

int DisplayVideo(cv::String name)
{
	const String windowName = "C1.2";
	namedWindow(windowName, WINDOW_AUTOSIZE);

	VideoCapture cap;
	if (!cap.open(name))
	{
		return -1;
	}

	Mat frame;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			// Ran out of film
			break;
		}
		imshow(windowName, frame);
		if (waitKey(33) >= 0)
		{
			break;
		}
	}

	destroyWindow(windowName);
	return 0;
}

int TestDisplayVideo()
{
	return DisplayVideo("../Assets/test.mp4");
}
