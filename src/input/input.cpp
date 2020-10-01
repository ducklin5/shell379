#include "input.h"

#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>

using std::cout;
using std::string;

int Input::getch() {
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);  // save old term attribs
	t_new = t_old;			  // copy to new variable
	t_new.c_lflag &=
	    ~(ICANON | ECHO);  // disable canonical mdoe and echo mode
	tcsetattr(STDIN_FILENO, TCSANOW,
		  &t_new);  // set new term attribs

	ch = getchar();	 // getchar

	tcsetattr(STDIN_FILENO, TCSANOW,
		  &t_old);  // reset old term attribs

	return ch;
}

void Input::cursorToHome() {
	for (; curPos > 0; curPos--) cout << '\b';
}

void Input::cursorToEnd() {
	printInput(-1);
}

void Input::clearInput() {
	cursorToHome();
	for (; curPos < (int)result.length(); curPos++) cout << " ";
	cursorToHome();
}

void Input::printInput( int newPos ) {
	cursorToHome();
	cout << result;
	for (curPos=(int)result.length() ; curPos>newPos && newPos>0; curPos--)
		cout << '\b';
}

void Input::handleEscLSBracket() {
	switch (getch()) {
		case UP:
			cout << "UP";
			break;
		case DOWN:
			cout << "DOWN";
			break;
		case RIGHT:
			if (curPos < (int)result.length()) {
				cout << result.at(curPos);
				curPos++;
			}
			break;
		case LEFT:
			if (curPos > 0) {
				cout << '\b';
				curPos--;
			}
			break;
		case HOME:;
			cursorToHome();
			getch();
			break;
		case END:
			cursorToEnd();
			getch();
			break;
	}
}

void Input::handleESC() {
	switch (getch()) {
		case LSBRACKET:
			handleEscLSBracket();
			break;
	}
}

int Input::grabInput(string& resultDest) {
	result = "";
	curPos = 0;
	int ch = 0;

	bool done = false;
	while (!done) {
		ch = getch();
		switch (ch) {
			case '\r':
			case '\n':
				done = true;
				break;

			case BACKSPACE:
				if (result.length() > 0 && curPos > 0) {
					int newPos = curPos-1;
					clearInput();
					result.erase(newPos, 1);
					printInput(newPos);
				}
				break;

			case ESC:
				handleESC();
				break;

			default:
				if(isprint(ch)) {
					result.insert(curPos, 1, ch);
					printInput(curPos + 1);
					break;
				}
		}
	}

	resultDest = result;
	return 0;
}

// https://man7.org/linux/man-pages/man3/termios.3.html
// http://www.cplusplus.com/articles/E6vU7k9E/#UNIX-e2
// https://stackoverflow.com/questions/61831114/c-how-to-get-input-from-the-arrow-keys-with-linux
