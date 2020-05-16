#include "C1_3_MovingAround.h"
#include <iostream>

using namespace cv;
using namespace std;

int g_slider_position = 0;
// start out in single step mode
int g_run = 1, g_dontset = 0;
VideoCapture g_cap;

void onTrackbarSlide(int pos, void*)
{
	// if user clicked on the trackbar to jump a new location in the video
	g_cap.set(CAP_PROP_POS_FRAMES, pos);

	if (!g_dontset)
	{
		// go into single step mode only if the callback was triggered by a user click
		g_run = 1;
	}
	g_dontset = 0;
}

int MovingAround(cv::String name)
{
	const String windowName = "C1.3";
	if (!g_cap.open(name))
	{
		return -1;
	}

	namedWindow(windowName, WINDOW_AUTOSIZE);

	int frames = (int)g_cap.get(CAP_PROP_FRAME_COUNT);
	int videoW = (int)g_cap.get(CAP_PROP_FRAME_WIDTH);
	int videoH = (int)g_cap.get(CAP_PROP_FRAME_HEIGHT);

	cout << "Video has " << frames << " frames of size " << videoW << "x" << videoH << endl;

	const String trackbarName = "Position";
	createTrackbar(trackbarName, windowName, &g_slider_position, frames, onTrackbarSlide);

	Mat frame;
	while (true)
	{
		if (g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty())
			{
				break;
			}

			int currentPos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
			// will not put us into single step mode
			g_dontset = 1;

			setTrackbarPos(trackbarName, windowName, currentPos);
			imshow(windowName, frame);

			g_run -= 1;
		}

		int key = waitKey(10);
		if (key == 's')
		{
			// single step
			g_run = 1;
		}
		else if (key == 'r')
		{
			g_run = -1;
		}
		else if (key == 27)
		{
			break;
		}
	}

	destroyWindow(windowName);
	return 0;
}

int TestMovingAround()
{
	g_slider_position = 0;
	// start out in single step mode
	g_run = 1; 
	g_dontset = 0;

	return MovingAround("../Assets/test.mp4");
}