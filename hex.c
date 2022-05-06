#include "hex.h"

lpByteArray LoadFromFile(const char* fname)
{
	FILE* file;
	size_t fsize;
	lpByteArray result;

	file = fopen(fname, "rb");

	if (!file)
		return NULL;

	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	/* add avail memomry check */

	result = (lpByteArray)malloc(sizeof(ByteArray));
	if (!result)
	{
		fclose(file);
		return NULL;
	}

	result->bytes = (uint8_t*)malloc(fsize);
	if (!result->bytes)
	{
		fclose(file);
		free(result);
		return NULL;
	}
	fread(result->bytes, 1, fsize, file);
	result->size = fsize;

	return result;
}