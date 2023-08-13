#include "String.h"

string::string()
{

}

string::string(char* aBuffer, int aLength)
{
	m_Buffer = aBuffer;
	m_Length = aLength;
}

string::~string()
{
	if (m_Buffer)
		delete[] m_Buffer;
}

char* string::String()
{
	return m_Buffer;
}

int string::Length()
{
	return m_Length;
}
