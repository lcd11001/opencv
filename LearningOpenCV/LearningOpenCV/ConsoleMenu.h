#pragma once
#include <stack>
#include <iostream>
#include <windows.h>

using namespace std;

typedef int (*MENU_FUNCTION_POINTER)();

typedef struct _MENU MENU;
typedef MENU* MENU_POINTER;

struct _MENU
{
	bool isValid; // C++ can not compare struct is NULL
	string text;
	MENU_FUNCTION_POINTER func;

	bool isOpen;
	MENU_POINTER childMenu;
	MENU_POINTER parent;
};

class ConsoleMenu
{
public:
	static ConsoleMenu* GetInstance();
	~ConsoleMenu();

	void Run();

private:
	ConsoleMenu(); // as we used singleton
	void Update();
	void UpdateKey();
	
	int GetKey(int& speckey);
	int GetMenuLength(MENU_POINTER menu);
	int ShowChildMenu(int index);
	int HideChildMenu(int index);
	void SetColor(int bg, int fg);
	
	void Render();
	void RenderMenu(MENU_POINTER menu, int deep);
	void RenderMenuItem(MENU item, int deep, bool selected);

	int Action();

private:
	bool mIsExit;
	bool mIsActive;

	int mIndex;
	int mTotal;
	bool mRefresh;
	MENU_POINTER mMenu;
	stack<int> mLastIndex;


private:
	static ConsoleMenu* _instance;
	static HANDLE _console;
	static MENU _chapters[];
	static MENU _chapter1[];
	static MENU _chapter2[];
};

