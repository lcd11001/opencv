#include "C1_7_PixelColor.h"
using namespace cv;

int ReadWriteColor(cv::String name)
{
	Mat img_rgb, img_gray, img_canny;

	img_rgb = imread(name);
	if (img_rgb.empty())
	{
		return 1;
	}

	const String nameWindow1 = "rgb";
	const String nameWindow2 = "canny";
	String nameColor;

	int x = 75, y = 250;
	//int x = 446, y = 180;
	const Vec3b& color = ReadPixel(img_rgb, x, y);
	std::stringstream s;
	s << " color RGB " << (unsigned int)color[2] << ":" << (unsigned int)color[1] << ":" << (unsigned int)color[0];
	nameColor = s.str();
	std::cout << nameColor << std::endl;

	namedWindow(nameWindow1 + nameColor);
	namedWindow(nameWindow2);

	pyrDown(img_rgb, img_canny); // img_canny is temp
	cvtColor(img_canny, img_gray, cv::COLOR_BGR2GRAY);
	Canny(img_gray, img_canny, 10, 100, 3, true);

	WritePixel(img_rgb, x, y, Vec3b(255, 0, 255), 3);
	WritePixel(img_canny, x / 2 , y /2 , Vec3b(255, 0, 255), 3); // as we use pyramid downsample 1 time

	imshow(nameWindow1 + nameColor, img_rgb);
	imshow(nameWindow2, img_canny);

	waitKey(0);

	destroyWindow(nameWindow1 + nameColor);
	destroyWindow(nameWindow2);

	return 0;
}

int TestReadWriteColor()
{
	return ReadWriteColor("../Assets/test512.png");
}

const cv::Vec3b& ReadPixel(const cv::Mat& img, int x, int y)
{
	const Vec3b& bgr = img.at<Vec3b>(Point(x, y));
	std::cout << "color at (" << x << ":" << y << ") red " << (unsigned int)bgr[2] << " green " << (unsigned int)bgr[1] << " blue " << (unsigned int)bgr[0] << std::endl;
	return bgr;
}

void WritePixel(cv::Mat& img, int x, int y, Vec3b color, int expand)
{
	std::cout << "image chanels " << img.channels() << std::endl;
	int chanels = img.channels();
	if (chanels == 3)
	{
		for (int r = y - expand; r < y + expand + 1; r++)
		{
			for (int c = x - expand; c < x + expand + 1; c++)
			{
				img.at<Vec3b>(Point(c, r)) = color;
			}
		}
	}
	else if (chanels == 1)
	{
		for (int r = y - expand; r < y + expand + 1; r++)
		{
			for (int c = x - expand; c < x + expand + 1; c++)
			{
				img.at<uchar>(Point(c, r)) = color[0];
			}
		}
	}
}
