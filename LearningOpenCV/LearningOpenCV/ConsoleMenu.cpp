#include "ConsoleMenu.h"
#include <conio.h>

#include "C1_1_DisplayPicture.h"

ConsoleMenu* ConsoleMenu::_instance = NULL;
HANDLE ConsoleMenu::_console = GetStdHandle(STD_OUTPUT_HANDLE);

int Example1()
{
	cout << "Example 1" << endl;
	return 0;
}

int Example2()
{
	cout << "Example 2" << endl;
	return 0;
}

MENU ConsoleMenu::_chapters[] = {
	{true, "Chapter 1", NULL, false, ConsoleMenu::_chapter1, NULL},
	{true, "Chapter 2", NULL, false, ConsoleMenu::_chapter2, NULL},
	{true, "Chapter 3", NULL, false, NULL, NULL},
	{true, "Chapter 4", NULL, false, NULL, NULL},
	{false, "unused", NULL, false, NULL, NULL}
};

MENU ConsoleMenu::_chapter1[] = {
	{true, "Display a picture", TestDisplayPicture, false, NULL, ConsoleMenu::_chapters},
	{true, "Example 1.2", Example2, false, NULL, ConsoleMenu::_chapters},
	{false, "unused", NULL, false, NULL, NULL}
};

MENU ConsoleMenu::_chapter2[] = {
	{true, "Example 2.1", NULL, false, NULL, ConsoleMenu::_chapters},
	{true, "Example 2.2", NULL, false, NULL, ConsoleMenu::_chapters},
	{true, "Example 2.3", NULL, false, NULL, ConsoleMenu::_chapters},
	{false, "unused", NULL, false, NULL, NULL}
};

ConsoleMenu* ConsoleMenu::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new ConsoleMenu();
	}
	return _instance;
}

ConsoleMenu::ConsoleMenu()
{
	mIsExit = false;
	mIndex = 0;
	mTotal = GetMenuLength(ConsoleMenu::_chapters);
	mMenu = ConsoleMenu::_chapters;
	mRefresh = true;
}

void ConsoleMenu::Update()
{
	UpdateKey();
}

void ConsoleMenu::UpdateKey()
{
	int speckey;
	int key = GetKey(speckey);
	if (key == 0)
	{
		key = speckey;
	}

	switch (key)
	{
	case 80:
		// DOWN
		mIndex = (mIndex + 1) % mTotal;
		mRefresh = true;
		break;

	case 72:
		// UP
		mIndex = (mTotal + (mIndex - 1) % mTotal) % mTotal;
		mRefresh = true;
		break;

	case 77:
		// RIGHT
		mIndex = ShowChildMenu(mIndex);
		mTotal = GetMenuLength(mMenu);
		mRefresh = true;
		break;

	case 75:
		// LEFT
		mIndex = HideChildMenu(mIndex);
		mTotal = GetMenuLength(mMenu);
		mRefresh = true;
		break;

	case 13:
	{
		// ENTER
		int errorCode = Action();
		if (errorCode != 0)
		{
			SetColor(0, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "errorCode " << errorCode << endl;
			SetColor(0, 15);
		}
		break;
	}

	case 27:
		// ESC
		mIsExit = true;
		break;
	default:
		cout << "press " << key << endl;
		break;
	}
}

void ConsoleMenu::Render()
{
	if (mRefresh)
	{
		mRefresh = false;

		// clear console screen
		system("cls");

		RenderMenu(ConsoleMenu::_chapters, 0);
	}
}

void ConsoleMenu::RenderMenu(MENU_POINTER menu, int deep)
{
	if (menu == NULL)
	{
		return;
	}

	int i = 0;
	while (/*menu[i] != NULL &&*/ menu[i].isValid)
	{
		RenderMenuItem(menu[i], deep, i == mIndex && mMenu == menu);
		if (menu[i].isOpen && menu[i].childMenu != NULL)
		{
			RenderMenu(menu[i].childMenu, deep + 1);
		}

		i++;
	}
}

void ConsoleMenu::RenderMenuItem(MENU item, int deep, bool selected)
{
	const int tab = 4;
	for (int i = 0; i < tab * deep; i++)
	{
		cout << " ";
	}

	if (selected)
	{
		// bg: red
		// fg: light yellow
		SetColor(BACKGROUND_RED, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}

	string prefix = " ";
	if (item.childMenu != NULL)
	{
		prefix = item.isOpen ? "-" : "+";
	}

	cout << prefix << item.text << endl;

	// reset to default color
	// bg: black
	// fg: white
	SetColor(0, 15);
}

int ConsoleMenu::Action()
{
	if (mMenu[mIndex].func != NULL)
	{
		return mMenu[mIndex].func();
	}

	SetColor(0, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "You clicked " << mMenu[mIndex].text << endl;
	SetColor(0, 15);

	return 0;
}

int ConsoleMenu::GetKey(int& speckey)
{
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=vs-2019
	int ch = _getch();
	if (ch == 0 || ch == 0xE0)
	{
		ch = 0;
		speckey = _getch();
	}
	return ch;
}

int ConsoleMenu::GetMenuLength(MENU_POINTER menu)
{
	int len = 0;
	while (menu[len].isValid)
	{
		len++;
	}
	return len;
}

int ConsoleMenu::ShowChildMenu(int index)
{
	if (mMenu[index].childMenu != NULL)
	{
		mLastIndex.push(index);

		mMenu[index].isOpen = true;
		mMenu = mMenu[index].childMenu;

		return 0;
	}

	return index;
}

int ConsoleMenu::HideChildMenu(int index)
{
	if (mMenu[index].parent != NULL)
	{
		mMenu = mMenu[index].parent;

		int prevIndex = mLastIndex.top();
		mMenu[prevIndex].isOpen = false;

		mLastIndex.pop();
		return prevIndex;
	}

	return index;
}

void ConsoleMenu::SetColor(int bg, int fg)
{
	int color = (bg & 0xF0) | (fg & 0x0F);
	SetConsoleTextAttribute(_console, color);
}

ConsoleMenu::~ConsoleMenu()
{
}

void ConsoleMenu::Run()
{
	while (!mIsExit)
	{
		Render();
		Update();
	}
}
