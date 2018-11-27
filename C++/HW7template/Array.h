#pragma once

#include <iostream>

template <class T>
class Array
{
	public:
		explicit Array(size_t size, const T& value);
		explicit Array(size_t size);
		Array();
		Array(const Array& arg);
		
		Array& operator =(const Array& arg);
		
		const size_t size() const;
		
		T& operator [](const size_t ind);
		const T& operator [](const size_t ind) const;
		
		void clean();
		~Array();
	private:
		size_t mSize = 0;
		T* mArray;
};


template<typename T, typename Cmp>
const T minimum(const Array<T>& arg, const Cmp func);


template <typename T>
void flatten(const Array <Array<T>>& arg, std::ostream& out);

template <typename T>
void flatten(const Array<T>& arg, std::ostream& out);

#include "Array.hpp"
