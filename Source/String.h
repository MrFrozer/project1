#pragma once

class String
{
public:
	String(void);
	String(const char* cstring);

	/*
		Info: Return char string data
		Type: (Read-Only)
	*/
	char* getData(void) const
	{
		return data;
	}
private:
	char* data;
	size_t length;
};

