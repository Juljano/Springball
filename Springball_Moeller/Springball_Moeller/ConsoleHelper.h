#include <iostream>
using namespace std;

class ConsoleHelper

{

public:

	void gotoXY(int x, int y);

	void hideCursor();

	string printEscaped(string escapable);

	void clearScreen();

};
