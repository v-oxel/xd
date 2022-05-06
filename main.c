#include "hex.h"

#include <wchar.h>

int main(int argc, const char* argv[])
{

	ByteArray* a = LoadFromFile("C:\\Users\\v_oxel\\source\\repos\\xd\\x64\\Release\\xd.exe");
	//ByteArray* a = LoadFromFile("C:\\Users\\v_oxel\\source\\repos\\xd\\xd\\main.cpp");

	if (!a)
	{
		printf("U suck!\n");
		return 1;
	}
	else
		printf("Succsess!\n");
	for (size_t i = 0; i < a->size; ++i)
		printf("%02x ", a->bytes[i]);
	free(a);
	printf("\nhello\n");
	return 0;
}