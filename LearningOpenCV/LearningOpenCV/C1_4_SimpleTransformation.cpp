#include "C1_4_SimpleTransformation.h"

using namespace cv;

int SimpleTransformation(cv::String name)
{
	const String windowOutputName = "C1.4 out";
	const String windowInputName = "C1.4 in";

	namedWindow(windowInputName, WINDOW_AUTOSIZE);
	namedWindow(windowOutputName, WINDOW_AUTOSIZE);

	Mat image = imread(name);
	if (image.empty())
	{
		return -1;
	}

	Mat output;
	GaussianBlur(image, output, Size(5, 5), 3, 3);
	GaussianBlur(output, output, Size(5, 5), 3, 3);

	imshow(windowInputName, image);
	imshow(windowOutputName, output);

	waitKey(0);

	destroyWindow(windowInputName);
	destroyWindow(windowOutputName);

	return 0;
}

int TestSimpleTransformation()
{
	return SimpleTransformation("../Assets/test512.png");
}
