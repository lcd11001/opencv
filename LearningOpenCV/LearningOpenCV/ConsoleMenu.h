#pragma once
#include <stack>
#include <iostream>
#include <windows.h>

using namespace std;

typedef void (*MENU_FUNCTION_POINTER)();

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
	void ShowChildMenu(int index);
	void HideChildMenu(int index);
	void SetColor(int bg, int fg);
	
	void Render();
	void RenderMenu(MENU_POINTER menu);
	void RenderMenuItem(MENU item);

private:
	bool mIsExit;
	int mIndex;
	int mTotal;
	bool mRefresh;
	MENU_POINTER mMenu;
	stack<int> mLastIndex;


private:
	static ConsoleMenu* _instance;
	static HANDLE _console;
};
