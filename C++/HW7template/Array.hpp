#include "Array.h"

template<class T>
Array<T>::Array(size_t size, const T& value) : mSize(size)
{
	mArray = reinterpret_cast <T*>(new char[mSize * sizeof(T)]);
	for (size_t i = 0; i < mSize; ++i)
	{
		new (mArray + i) T(value);
	}
}

template<class T>
Array<T>::Array(size_t size) : mSize(size)
{
	mArray = reinterpret_cast <T*>(new char[mSize * sizeof(T)]);
	for (size_t i = 0; i < mSize; ++i)
	{
		new (mArray + i) T();
	}
}

template<class T>
Array<T>::Array()
{
	mSize = 0;
	mArray = nullptr;
}

template<class T>
Array<T>::Array(const Array<T>& arg) : mSize(arg.size())
{
	mArray = reinterpret_cast <T*>(new char[mSize * sizeof(T)]);
	for (size_t i = 0; i < mSize; ++i)
	{
		new (mArray + i) T(arg[i]);
	}
}


template<class T>
Array<T>& Array<T>::operator =(const Array<T>& arg)
{
	if (this != &arg)
	{
		clean();
		mSize = arg.mSize;
		mArray = reinterpret_cast <T*>(new char[mSize * sizeof(T)]);
		for (size_t i = 0; i < mSize; ++i)
		{
			new (mArray + i) T(arg[i]);
		}
	}
	return *this;
}

template<class T>
const size_t Array<T>::size() const
{
	return mSize;
}


template<class T>
T& Array<T>::operator [](const size_t ind)
{
	return mArray[ind];
}

template<class T>
const T& Array<T>::operator [](const size_t ind) const
{
	return mArray[ind];
}


template<class T>
void Array<T>::clean()
{
    for (size_t i = 0; i < mSize; ++i)
	{
		mArray[i].~T();
	}
	delete[] (char*) mArray;
}

template<class T>
Array<T>::~Array()
{
	clean();
}


template<typename T, typename F>
const T minimum(const Array<T>& arg, const F cmp)
{
	size_t min = 0;
	for (size_t i = 1; i < arg.size(); ++i)
	{
		if (cmp(arg[i], min))
		{
			min = i;
		}
	}
	return arg[min];
}


template <typename T>
void flatten(const Array <Array<T>>& arg, std::ostream& out)
{
    for (size_t i = 0; i < arg.size(); ++i)
	{
        flatten(arg[i], out);
    }
}

template <typename T>
void flatten(const Array<T>& arg, std::ostream& out)
{
    for (size_t i = 0; i < arg.size(); ++i)
	{
        out << arg[i] << ' ';
    }
}
