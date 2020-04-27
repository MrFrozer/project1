#include "String.h"

#include <iostream>


String::String(void)
{
	data = nullptr;
	length = 0;
}

String::String(const char* cstring)
{
	length = strlen(cstring);
	data = new char[length + 1];

	for (size_t i = 0; i < length; i++)
		data[i] = cstring[i];

	data[length] = '\0';
}

char* String::getData(void) const
{
	return data;
}
