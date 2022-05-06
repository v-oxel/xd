#include "console.h"

void UpdateConsole(lpConsole console)
{
	int cols;
	int rows;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	rows = w.ws_row;
	cols = w.ws_col;
#endif
	
}

void WriteInConsole(lpConsole console, int col, int row, const char* string)
{
}