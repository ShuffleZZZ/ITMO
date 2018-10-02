#include <iostream>

class Complex {
	private:
		int real, im;
	public:
		Complex() {
			real = 0;
			im = 0;
		}
		Complex(int a, int b) {
			real = a;
			im = b;
		}
		Complex multiply(Complex b) {
			Complex c;
			c.real = real * b.real - im * b.im;
			c.im = real * b.im + b.real * im;
			return c;
		}
		void changeReal(int a) {
			real = a;
		}
		void changeIm(int a) {
			im = a;
		}
		int getReal() {
			return real;
		}
		int getIm() {
			return im;
		}
};

int main() {
	Complex a, b(0, 3);
	a.changeReal(1);
	a.changeIm(2);
	std::cout << a.getReal() << ' ' << a.getIm();
	Complex c = a.multiply(b);
	std::cout << '\n' << c.getReal() << ' ' << c.getIm();
}

