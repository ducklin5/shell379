#pragma once

#include <iostream>

class Input {
       private:
	static const char BACKSPACE = 127, ESC = 27, LSBRACKET = '[', UP = 'A',
			  DOWN = 'B', RIGHT = 'C', LEFT = 'D', HOME = '1',
			  END = '4';
	std::string result;
	int curPos;

	int getch();

	void cursorToHome();

	void cursorToEnd();

	void clearInput();

	void printInput( int newPos );

	void handleEscLSBracket();

	void handleESC();

       public:
	int grabInput(std::string& resultDest);
};

static Input InputManager;
