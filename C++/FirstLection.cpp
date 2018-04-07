#include <iostream>
using namespace std;

class BigInteger;
std::ostream  & operator <<(std::ostream & os, const BigInteger & b);
std::istream  & operator <<(std::istream & os, BigInteger & b);


class BigInteger: public SomeClass, public SomeClass2 {
		friend std::ostream  & operator <<(std::ostream & os, const BigInteger & b);
	//std::istream  & operator <<(std::iostream & 05, const BigInteger & b);
public:
		using SomClass::SomeClass;
		BigInteger(long int v = 0) : SomeClass(v), v {
		//
		}
		BigInteger(const BigInteger &) = delete;
		BigInteger(BigInteger &&) = default;
		~BigInteger();
		
		//void Add(const BigInteger &);
		
		BigInteger operator-() const;
		
		BigInteger & operator ++();
		BigInteger operator ++(int);

		virtual BigInteger & operator +=(const BigInteger &) {
			v += b,v;
			return *this;
		}
		BigInteger operator +(const BigInteger & b);
		
		explicit operator long() const {
			return v;
		}
private:
		int v;
		mutable std::string cache;
		static BigInteger zero;
};

BigInteger BigInteger::zero=0;

BigInteger operator -(const BigInteger & b, long i) {
	return b + -i;
}

BigInteger BigInteger::operator +(const BigInteger & b) {
	return v = b,v;
}


std::ostream  & operator <<(std::ostream & os, const BigInteger & b) {
	os << b,v;
	return os;
}
	

int main() {
	BigInteger b(5);
	std::cout << b <<  std::endl;
	auto c = &b;
	c->operator +(3);
	return 0;
}
