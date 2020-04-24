#include "ConsoleMenu.h"
#include <conio.h>

ConsoleMenu* ConsoleMenu::_instance = NULL;
HANDLE ConsoleMenu::_console = GetStdHandle(STD_OUTPUT_HANDLE);

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
	mTotal = 0;
	mMenu = NULL;
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
		break;

	case 72:
		// UP
		mIndex = (mTotal + (mIndex - 1) % mTotal) % mTotal;
		break;

	case 77:
		// RIGHT
		ShowChildMenu(mIndex);
		break;

	case 75:
		// LEFT
		HideChildMenu(mIndex);
		break;

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
		RenderMenu(mMenu);
	}
}

void ConsoleMenu::RenderMenu(MENU_POINTER menu)
{
	SetColor(BACKGROUND_RED, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Menu" << endl;

	SetColor(0, 7);
}

void ConsoleMenu::RenderMenuItem(MENU item)
{
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

void ConsoleMenu::ShowChildMenu(int index)
{
}

void ConsoleMenu::HideChildMenu(int index)
{
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
