#include <iostream>

using namespace std;

int main() {
	unsigned n;
	cin >> n;
	while (true) {
		char s;
		cin >> s;
		switch(s) {
			case('I'):
				int a, b, D;
				cin >> a >> b >> D;
				break;
			case('Q'):
				int h;
				cin >> h;
				break;
			case('E'):
				return;
		}
	}
}
