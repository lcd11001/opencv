#pragma once
#include "ConsoleMenu.h"

#include "C1_1_DisplayPicture.h"
#include "C1_2_DisplayVideo.h"
#include "C1_3_MovingAround.h"
#include "C1_4_SimpleTransformation.h"
#include "C1_5_PyramidDown.h"
#include "C1_6_EdgeDetector.h"
#include "C1_7_PixelColor.h"

MENU ConsoleMenu::_chapters[] = {
	{true, "Chapter 1", NULL, false, ConsoleMenu::_chapter1, NULL},
	{true, "Chapter 2", NULL, false, ConsoleMenu::_chapter2, NULL},
	{true, "Chapter 3", NULL, false, NULL, NULL},
	{true, "Chapter 4", NULL, false, NULL, NULL},
	{false, "unused", NULL, false, NULL, NULL}
};

MENU ConsoleMenu::_chapter1[] = {
	{true, "Display a picture", TestDisplayPicture, false, NULL, ConsoleMenu::_chapters},
	{true, "Display a video", TestDisplayVideo, false, NULL, ConsoleMenu::_chapters},
	{true, "Moving Around", TestMovingAround, false, NULL, ConsoleMenu::_chapters},
	{true, "Simple Transformation", TestSimpleTransformation, false, NULL, ConsoleMenu::_chapters},
	{true, "Pyramid Down Sample", TestPyramidDown, false, NULL, ConsoleMenu::_chapters},
	{true, "Edge Detector", TestEdgeDetector, false, NULL, ConsoleMenu::_chapters},
	{true, "Read Write Pixel Color", TestReadWriteColor, false, NULL, ConsoleMenu::_chapters},
	{false, "unused", NULL, false, NULL, NULL}
};

MENU ConsoleMenu::_chapter2[] = {
	{true, "Example 2.1", NULL, false, NULL, ConsoleMenu::_chapters},
	{true, "Example 2.2", NULL, false, NULL, ConsoleMenu::_chapters},
	{true, "Example 2.3", NULL, false, NULL, ConsoleMenu::_chapters},
	{false, "unused", NULL, false, NULL, NULL}
};