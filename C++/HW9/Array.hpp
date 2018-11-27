#include "Array.h"


template<class T>
Array<T>::Array(size_t size) : mSize(size)
{
	mData = new T[mSize];
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = 0;
	}
}

template<class T>
Array<T>::Array(const Array& a) : mSize(a.mSize)
{
	mData = new T[mSize];
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = a.mData[i];
	}
}

template<class T>
Array<T>::Array(Array && a) : mSize(a.mSize), mData(a.mData)
{
	a.mData = nullptr;
	a.mSize = 0;
}


template<class T>
Array<T>& Array<T>::operator =(const Array& a)
{
	mSize = a.mSize;
	delete[] mData;
	mData = new T[mSize];
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = a.mData[i];
	}
	return *this;
}

template<class T>
Array<T>& Array<T>::operator =(Array && a)
{
	delete[] mData;
	mData = a.mData;
	mSize = a.mSize;
	a.mData = nullptr;
	a.mSize = 0;
	return *this;
}


template<class T>
size_t Array<T>::size() const
{
	return mSize;
}


template<class T>
T& Array<T>::operator [](size_t i)
{
	return mData[i];
}

template<class T>
const T& Array<T>::operator [](size_t i) const
{
	return mData[i];
}


template<class T>
Array<T>::~Array()
{
	delete[] mData;
}
