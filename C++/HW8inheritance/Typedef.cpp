int* (*(*ComplexFunction)(int, int (*)(double)))(const char*);
//same as
typedef int* (*FinalFunction)(const char*); //const char* == char const *
typedef int (*MidFunction)(double);
typedef FinalFunction (*ComplexFunction)(int, MidFunction);
