#ifndef CONSOLE_H
#define CONSOLE_H

#ifndef __cplusplus
/*
extern "C" {
*/
#endif

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>

/*
 offset | bytes    | decoded_txt | data_inspector
--------+----------+-------------+----------------
 9      | (3 * 16) | 17          | 9 20
*/

struct _Console;
typedef struct _Console Console;
typedef Console* lpConsole;

struct _Console
{
	int cols;
	int rows;

	char* buffer;
};

void UpdateConsole(lpConsole console);
void WriteInConsole(lpConsole console, int col, int row, const char* string);

#ifndef __cplusplus
/*
}
*/
#endif

#endif