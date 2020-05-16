#pragma once
#include <opencv2/opencv.hpp>

int ReadWriteColor(cv::String name);
int TestReadWriteColor();

const cv::Vec3b& ReadPixel(const cv::Mat& img, int x, int y);
void WritePixel(cv::Mat& img, int x, int y, cv::Vec3b color, int expand = 0);

