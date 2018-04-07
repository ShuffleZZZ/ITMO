#include <vector>

#progma once

#if HAVE_MOVE
		Class(Class&&) ...
#endif

#ifndef SOME_GUARD
#define SOME_GUARD

.....

std::vector<int> v;

template<typename T, int = 1>
class C {
	T v;
};

template<int a, int b>
class C<int, a> {
	
};

template<typename... A>
void foo(A... args) {
	
}

template<typename T>
typename std::enable_if<std::is_same<T, int::value, void>::type foo(t, v);


C<int> c;

auto n = 1; //same
decltype(1) n = 1; //same

static_assert(true, "dd");

std::function<double(int)> f = [a, &f](int p ) -> double {
	return p;
};
