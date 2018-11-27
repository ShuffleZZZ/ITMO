#include <iostream>
#include <algorithm>

#include "String.h"

String::String(const int size = 0) : mSize(size), mStr(new char[mSize + 1])
{
	for (int i = 0; i < mSize; ++i)
	{
		mStr[i] = ' ';
	}
	mStr[mSize] = '0';
}

String::String(const std::string arg) :
 			   mSize(arg.size() - 1), mStr(new char[mSize + 1])
{
	for (int i = 0; i <= mSize; ++i)
	{
		mStr[i] = arg[i];
	}
}

String::String(const int amount,const char fill) : 
			   mSize(amount), mStr(new char[mSize + 1])
{
	for (int i = 0; i < mSize; ++i)
	{
		mStr[i] = fill;
	}
	mStr[mSize] = '0';
}

String::String(const String& arg) :
 			   mSize(arg.getSize()), mStr(new char[mSize + 1])
{
	for (int i = 0; i <= mSize; ++i)
	{
		mStr[i] = arg.mStr[i];
	}
}


void String::append(const String& arg)
{
	String buffer(mSize + arg.getSize());
	for (int i = 0; i < mSize; ++i)
	{
		buffer.mStr[i] = mStr[i];
	}
	for (int i = 0; i < arg.getSize(); ++i)
	{
		buffer.mStr[i + mSize] = arg.mStr[i];
	}
	swap(buffer);
}

void String::swap(String& arg)
{
	std::swap(mSize, arg.mSize);
	std::swap(mStr, arg.mStr);
}

void String::reverse()
{
	for (int i = 0; i < mSize >> 1; ++i)
	{
		std::swap(mStr[i], mStr[mSize - 1 - i]);
	}
}

void String::copy(const int begin, const int end, String& out)
{
	std::string arg = "";
	for (int i = begin; i < end; ++i)
	{
		arg += mStr[i];
	}
	arg += '0';
	out = arg;
}

short String::strcmp(const String& arg) const
{
	int minSize = mSize < arg.mSize ? mSize : arg.mSize;
	for (int i = 0; i < minSize; ++i)
	{
		if (mStr[i] > arg.mStr[i])
		{
			return 1;
		} else if (mStr[i] < arg.mStr[i])
		{
			return -1;
		}
	}
	if (mSize == arg.mSize)
	{
		return 0;
	} else if (minSize == mSize)
	{
		return -1;
	} else
	{
		return 1;
	}
}


int String::getSize() const
{
	return mSize;
}

char* String::getStr() const
{
	return mStr;
}


String& String::operator =(const String& arg)
{
	if (this != &arg)
	{
		String(arg).swap(*this);
	}
	return *this;
}


bool String::operator <(const String& second) const
{
	return (*this).strcmp(second) < 0;
}

bool String::operator >(const String& second) const
{
	return (*this).strcmp(second) > 0;
}

bool String::operator <=(const String& second) const
{
	return !((*this).strcmp(second) > 0);
}

bool String::operator >=(const String& second) const
{
	return !((*this).strcmp(second) < 0);
}

bool String::operator ==(const String& second) const
{
	return (*this).strcmp(second) == 0;
}

bool String::operator !=(const String& second) const
{
	return !((*this).strcmp(second) == 0);
}


String::~String()
{
	delete [] mStr;
}


std::ostream& operator <<(std::ostream& out, const String& arg)
{
	for (int i = 0; i < arg.getSize(); ++i)
	{
		out << (arg.getStr())[i];
	}
	return out;
}
