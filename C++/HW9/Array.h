#pragma once

template<class T>
class Array
{
	public:
		explicit Array(size_t size = 0);
		Array(const Array& a);
		Array(Array&& a); //move constructor.
		
		Array& operator =(const Array& a);
		Array& operator =(Array&& a); //move assigment opearator.
		
		size_t size() const;
		
		T& operator [](size_t i);
		const T& operator [](size_t i) const;
	
		~Array();
	private:
		size_t mSize;
		T* mData;
};

#include "Array.hpp"
