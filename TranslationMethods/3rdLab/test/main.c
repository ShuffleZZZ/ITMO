#include "stdio.h"

int nextInt() {
    int result;
    scanf("%d", &result);
    return result;
}

bool nextBool() {
    bool result;
    scanf("%d", &result);
    return result;
}

long long nextLong() {
    long long result;
    scanf("%lld", &result);
    return result;
}

double nextDouble() {
    double result;
    scanf("%lf", &result);
    return result;
}

char* nextLine() {
    char* result;
    size_t len = 0;
    getline(&result, &len, stdin);
    return result;
}

void print(int arg) {
    printf("%d", arg);
}

void print(long long arg) {
    printf("%lld", arg);
}

void print(double arg) {
    printf("%lf", arg);
}

void print(bool arg) {
    printf("%d", arg);
}

void print(char* arg) {
    printf("%s", arg);
}

double add(double a, double b) {
	return a + b;
}

void add5(int a) {
	int c;
	int c = a + 5;
}

bool empty() {
	bool l = true ^ true;
	bool m = true ^ false;
	if (add5(2)) {
		char* N5 = 'a';
	};
	return m ^ l;
}

int main() {
    char* d;
	if (d) {
		int a = 5 + 2 - 4;
	};
	if (d == "") {
		bool e = true || false;
	};
	int g = nextInt();
	int h = 1 + 2 - 3;
	long long i = nextLong();
	long long i1;
	long long i1 = i + 2343523565;
	double j = nextDouble();
	double j1;
	double j1 = j + 0.0;
	char* k = nextLine();
	char* k1;
	char* k1 = "asd" + k;
	int g = h;
	int h = g;
	int g = i1;
	int h = 123;
	long long i = g;
	long long i1 = h;
	char* z = k1;
	for (int n = 0; n <= h; n++) {
		print(n);
	};
	for (int n = -5; n <= 5; n++) {
		print(n-1);
	};
	int n;
	while (n) {
		int n = n % g;
	};
	
    return 0;
}