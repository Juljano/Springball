
#include "ConsoleHelper.h"
#include <iostream>
using namespace std;


	void ConsoleHelper::gotoXY(int x, int y) {

		cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
	}

	void ConsoleHelper::hideCursor() {

		cout << "\033[?25l";
	}

	string ConsoleHelper::printEscaped(string escapable) {
		char escCode = 0x1B;
		string printable = escCode + escapable;


		return printable;
	}

	void ConsoleHelper::clearScreen() {

		std::cout << "\033[2J"; 
		std::cout << "\033[H";

	}
