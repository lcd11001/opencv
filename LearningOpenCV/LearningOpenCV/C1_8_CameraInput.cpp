#include "C1_8_CameraInput.h"
using namespace cv;

int CameraInput()
{
	VideoCapture cap;
	if (!cap.open(0))
	{
		return -1;
	}

	const String windowName = "Camera input";
	namedWindow(windowName, cv::WINDOW_AUTOSIZE);

	bool isCapturing = true;
	Mat frame;
	while (isCapturing)
	{
		cap >> frame;
		// 0 means flipping around the x-axis => vertical flipping
		// 1 means flipping around y-axis => horizontal flipping
		// -1 means flipping around both axes 
		cv::flip(frame, frame, 1);
		if (frame.empty())
		{
			isCapturing = false;
		}

		imshow(windowName, frame);

		int key = waitKey(10);
		if (key == 27)
		{
			isCapturing = false;
		}
	}

	cap.release();
	destroyWindow(windowName);

	return 0;
}

int TestCameraInput()
{
	return CameraInput();
}