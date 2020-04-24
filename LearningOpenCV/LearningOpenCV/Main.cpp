#include <iostream>
#include "ConsoleMenu.h"

using namespace std;

void main()
{
	cout << "Learning OpenCV" << endl;

	ConsoleMenu::GetInstance()->Run();
}