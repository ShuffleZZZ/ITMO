#include <iostream>
#include <fstream>

#include <vector>
#include <string>

#include "Picture.h"


Picture::Picture(const unsigned int height = 0, const unsigned int width = 0)
				: mHeight(height), mWidth(width)
{
	mArray.resize(mHeight, std::vector <int> (mWidth, 0));
}

Picture::Picture(const Picture& arg) : mHeight(arg.mHeight), 
					mWidth(arg.mWidth), mArray(arg.mArray)
{}


void Picture::get(const std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	file >> (*this);
	file.close();
}


Picture Picture::operator +(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first + second;
			if (result[i][j] > COLOR_MASK)
			{
				result[i][j] = COLOR_MASK;
			}
		}
	}
	return result;
}

Picture Picture::operator -(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first - second;
			if (result[i][j] < 0)
			{
				result[i][j] = 0;
			}
		}
	}
	return result;
}

Picture Picture::operator *(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first * second;
			if (result[i][j] > COLOR_MASK)
			{
				result[i][j] = COLOR_MASK;
			}
		}
	}
	return result;
}


Picture& Picture::operator +=(const Picture& arg)
{
	Picture result = (*this) + arg;
	swap(result);
	return (*this);
}

Picture& Picture::operator -=(const Picture& arg)
{
	Picture result = (*this) - arg;
	swap(result);
	return (*this);
}

Picture& Picture::operator *=(const Picture& arg)
{
	Picture result = (*this) * arg;
	swap(result);
	return (*this);
}


Picture Picture::operator +(const int arg) const
{
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] += arg;
			if (result[i][j] > COLOR_MASK)
			{
				result[i][j] = COLOR_MASK;
			} else if (result[i][j] < 0)
			{
				result[i][j] = 0;
			}
		}
	}
	return result;
}

Picture Picture::operator -(const int arg) const
{
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] -= arg;
			if (result[i][j] > COLOR_MASK)
			{
				result[i][j] = COLOR_MASK;
			} else if (result[i][j] < 0)
			{
				result[i][j] = 0;
			}
		}
	}
	return result;
}

Picture Picture::operator *(const unsigned int arg) const
{
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] *= arg;
			if (result[i][j] > COLOR_MASK)
			{
				result[i][j] = COLOR_MASK;
			}
		}
	}
	return result;
}

Picture Picture::operator /(const unsigned int arg) const
{
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] /= arg;
		}
	}
	return result;
}

Picture Picture::operator %(const unsigned int arg) const
{
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] %= arg;
		}
	}
	return result;
}


Picture& Picture::operator +=(const int arg)
{
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] += arg;
			if ((*this)[i][j] > COLOR_MASK)
			{
				(*this)[i][j] = COLOR_MASK;
			} else if ((*this)[i][j] < 0)
			{
				(*this)[i][j] = 0;
			}
		}
	}
	return (*this);
}

Picture& Picture::operator -=(const int arg)
{
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] -= arg;
			if ((*this)[i][j] > COLOR_MASK)
			{
				(*this)[i][j] = COLOR_MASK;
			} else if ((*this)[i][j] < 0)
			{
				(*this)[i][j] = 0;
			}
		}
	}
	return (*this);
}

Picture& Picture::operator *=(const unsigned int arg)
{
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] *= arg;
			if ((*this)[i][j] > COLOR_MASK)
			{
				(*this)[i][j] = COLOR_MASK;
			}
		}
	}
	return (*this);
}

Picture& Picture::operator /=(const unsigned int arg)
{
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] /= arg;
		}
	}
	return (*this);
}

Picture& Picture::operator %=(const unsigned int arg)
{
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] %= arg;
		}
	}
	return (*this);
}


Picture& Picture::operator ~()
{
	 return (*this) ^= COLOR_MASK;
}


Picture Picture::operator ^(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first ^ second;
		}
	}
	return result;
}

Picture Picture::operator &(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first & second;
		}
	}
	return result;
}

Picture Picture::operator |(const Picture& arg) const
{
	const unsigned int maxHeight = std::max(mHeight, arg.mHeight);
	const unsigned int maxWidth = std::max(mWidth, arg.mWidth);
	Picture result(maxHeight, maxWidth);
	for (unsigned int i = 0; i < maxHeight; ++i)
	{
		for (unsigned int j = 0; j < maxWidth; ++j)
		{
			int first = 0;
			int second = 0; 
			if (i < mHeight && j < mWidth)
			{
				first = mArray[i][j];
			}
			if (i < arg.mHeight && j < arg.mWidth)
			{
				second = arg[i][j];
			}
			result[i][j] = first | second;
		}
	}
	return result;
}


Picture& Picture::operator ^=(const Picture& arg)
{
	Picture result = (*this) ^ arg;
	swap(result);
	return (*this);
}

Picture& Picture::operator &=(const Picture& arg)
{
	Picture result = (*this) & arg;
	swap(result);
	return (*this);
}

Picture& Picture::operator |=(const Picture& arg)
{
	Picture result = (*this) | arg;
	swap(result);
	return (*this);
}


Picture Picture::operator ^(const int arg) const
{
	const int edit = arg & COLOR_MASK;
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] ^= edit;
		}
	}
	return result;
}

Picture Picture::operator &(const int arg) const
{
	const int edit = arg & COLOR_MASK;
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] &= edit;
		}
	}
	return result;
}

Picture Picture::operator |(const int arg) const
{
	const int edit = arg & COLOR_MASK;
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] |= edit;
		}
	}
	return result;
}

Picture Picture::operator >>(const unsigned int arg) const
{
	const unsigned int edit = arg > COLOR_BITS ? COLOR_BITS : arg;
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] >>= edit;
		}
	}
	return result;
}

Picture Picture::operator <<(const unsigned int arg) const
{
	const unsigned int edit = arg > COLOR_BITS ? COLOR_BITS : arg;
	Picture result(*this);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] <<= edit;
		}
	}
	return result;
}


Picture& Picture::operator ^=(const int arg)
{
	const int edit = arg & COLOR_MASK;
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] ^= arg;
		}
	}
	return (*this);
}

Picture& Picture::operator &=(const int arg)
{
	const int edit = arg & COLOR_MASK;
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] &= arg;
		}
	}
	return (*this);
}

Picture& Picture::operator |=(const int arg)
{
	const int edit = arg & COLOR_MASK;
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] |= arg;
		}
	}
	return (*this);
}

Picture& Picture::operator >>=(const unsigned int arg)
{
	const unsigned int edit = arg > COLOR_BITS ? COLOR_BITS : arg;
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] >>= arg;
		}
	}
	return (*this);
}

Picture& Picture::operator <<=(const unsigned int arg)
{
	const unsigned int edit = arg > COLOR_BITS ? COLOR_BITS : arg;
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			(*this)[i][j] <<= arg;
		}
	}
	return (*this);
}


bool Picture::operator <(const Picture& r) const
{
	return (*this).cmp(r) < 0;
}

bool Picture::operator <=(const Picture& r) const
{
	return !((*this).cmp(r) > 0);
}

bool Picture::operator >(const Picture& r) const
{
	return (*this).cmp(r) > 0;
}

bool Picture::operator >=(const Picture& r) const
{
	return !((*this).cmp(r) < 0);
}

bool Picture::operator ==(const Picture& r) const
{
	return (*this).cmp(r) == 0;
}

bool Picture::operator !=(const Picture& r) const
{
	return (*this).cmp(r) != 0;
}


Picture& Picture::operator +()
{
	Picture result(mWidth, mHeight);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[j][mHeight - i - 1] = mArray[i][j];
		}
	}
	swap(result);
	return *this;
}

Picture& Picture::operator -()
{
	Picture result(mWidth, mHeight);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[mWidth - j - 1][i] = mArray[i][j];
		}
	}
	swap(result);
	return *this;
}


void Picture::operator ++()
{
	++mHeight;
	mArray.insert(mArray.begin(), std::vector <int> (mWidth, 0));
}

void Picture::operator --()
{
	--mHeight;
	mArray.erase(mArray.begin());
}

void Picture::operator ++(const int)
{
	++mHeight;
	mArray.push_back(std::vector <int> (mWidth, 0));
}

void Picture::operator --(const int)
{
	--mHeight;
	mArray.erase(mArray.end());
}


Picture::operator bool() const
{
	return !mArray.empty();
}

Picture::operator !() const
{
	return !bool(*this);
}

bool Picture::operator &&(const Picture& r) const
{
	return bool(*this) && bool(r);
}

bool Picture::operator ||(const Picture& r) const
{
	return bool(*this) || bool(r);
}


Picture& Picture::operator =(const Picture& arg)
{
	if (this != &arg)
	{
		Picture(arg).swap(*this);
	}
	return *this;
}


Picture Picture::operator ,(const Picture& arg) const
{
	Picture result(mHeight, mWidth + arg.mWidth);
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = 0; j < mWidth; ++j)
		{
			result[i][j] = mArray[i][j];
		}
	}
	for (unsigned int i = 0; i < mHeight; ++i)
	{
		for (unsigned int j = mWidth; j < result.mWidth; ++j)
		{
			result[i][j] = arg[i][j - mWidth];
		}
	}
	return result;
}


void Picture::operator ->*(const std::string fileName) const
{
	std::ofstream file;
	file.open(fileName);
	file << (*this);
	file.close();
}


std::vector <int>& Picture::operator [](const unsigned int i)
{
	return mArray[i];
}

const std::vector <int>& Picture::operator [](const unsigned int i) const
{
	return mArray[i];
}


unsigned int Picture::getHeight() const
{
	return mHeight;
}

unsigned int Picture::getWidth() const
{
	return mWidth;
}

void Picture::swap(Picture& arg)
{
	std::swap(mHeight, arg.mHeight);
	std::swap(mWidth, arg.mWidth);
	std::swap(mArray, arg.mArray);
}
	

Picture::~Picture()
{
	mArray.clear();
}


short Picture::cmp(const Picture& r) const
{
	const unsigned int lResolution = mHeight * mWidth;
	const unsigned int rResolution = r.mHeight * r.mWidth;
	if (lResolution > rResolution)
	{
		return 1;
	} else if (rResolution < lResolution)
	{
		return -1;
	}
	return 0;
}


std::ostream& operator <<(std::ostream& out, const Picture& arg)
{
	out << FORMAT_TYPE << ' ' << arg.getWidth() << ' ' << arg.getHeight()
	<< ' ' << COLOR_MASK << ' ';
	for (unsigned int i = 0; i < arg.getHeight(); ++i)
	{
		for (unsigned int j = 0; j < arg.getWidth(); ++j)
		{
			out << (arg[i][j] ^ COLOR_MASK) << ' ';
		}
		out << '\n';
	}
	return out;
}

std::istream& operator >>(std::istream& in, Picture& arg)
{
	std::string tmp;
	unsigned int height, width;
	in >> tmp >> width >> height >> tmp;
	arg = Picture(height, width);
	for (unsigned int i = 0; i < arg.getHeight(); ++i)
	{
		for (unsigned int j = 0; j < arg.getWidth(); ++j)
		{
			in >> arg[i][j];
		}
	}
	~arg;
	return in;
}
