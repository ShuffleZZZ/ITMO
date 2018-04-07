#include <iostream>
#include <vector>
 
using namespace std;
 
const unsigned base = 1000000000;
const int pow = 9;

class BigInteger {
private:
    vector<int> elements;
    bool sign = false;		
    static int compare(BigInteger a, BigInteger b){
        if (a.elements.size() > b.elements.size()){
            return 1;
        }
        if (a.elements.size() < b.elements.size()){
            return 0;
        }
        for (int i = a.elements.size() - 1; i >= 0; i--){
			if (a.elements[i] < b.elements[i]) {
				return 0;
			}
			if (a.elements[i] > b.elements[i]) {
				return 1;
			}
		}
        return 2;
    }	
    static BigInteger plus (BigInteger a, BigInteger b) {
        int left = 0;
        for (size_t i = 0; i < max(a.elements.size(), b.elements.size()) or left; i++) {
            if (i == a.elements.size()) {
                a.elements.push_back(0);
            }
           	a.elements[i] += left;
            if (i < b.elements.size()) {
            	a.elements[i] +=b.elements[i];
            }
            left = (a.elements[i] >= base);
            if (left) {
				a.elements[i] -= base;
			}
        }
        return a;
    }
    static BigInteger minus (BigInteger a, BigInteger b) {
        int left = 0;
        for (size_t i = 0; i < b.elements.size() or left; i++) {
        	if (i < b.elements.size()) {
        		a.elements[i] -= left + b.elements[i];
        	} else {
        		a.elements[i] -= left;
        	}
            left = (a.elements[i] < 0);
            if (left) {
				a.elements[i] += base;
			}
        }
        while ((a.elements.size() > 1) and (a.elements.back() == 0)) {
            a.elements.pop_back();
        }
        return a;
    }
    friend BigInteger operator+(BigInteger a, BigInteger b) {
        BigInteger c;
        if (a.sign == b.sign) {
            c = plus(a, b);
            c.sign = a.sign;
            return c;
        } else {
            if (compare(a, b) == 1) {
                c = minus(a, b);
                c.sign = a.sign;
                return c;
            } else {
                c = minus(b, a);
                c.sign = b.sign;
                return c;
            }
        }
    }
    friend BigInteger operator-(BigInteger a, BigInteger b) {
        BigInteger c;
        if (a.sign == b.sign) {
            if (compare(a, b) == 1) {
                c = minus(a, b);
                c.sign = a.sign;
                return c;
            } else if (compare(a, b) == 0) {
                c = minus(b, a);
                c.sign = !a.sign;
                return c;
            } else {
            	c = minus(b, a);
            	c.sign = false;
            	return c;
            }
        } else {
            if (compare(a, b) == 1) {
                c = plus(a, b);
                c.sign = a.sign;
                return c;
            } else if (compare(a, b) == 0) {
                c = plus(a, b);
                c.sign = a.sign;
                return c;
            } else {
            	c = plus(a, b);
            	c.sign = false;
            	return c;
            }
        }
    }
    friend BigInteger operator+=(BigInteger &a, BigInteger b) {
        a = a + b;
        return a;
    }
    friend BigInteger operator-=(BigInteger &a, BigInteger b) {
        a = a - b;
        return a;
    }
    friend ostream &operator<<(ostream &out, const BigInteger &b) {
        if (b.sign) {
			out << '-';
		}
        for (int i = b.elements.size() - 1; i >= 0; i--) {
        	if ((b.elements.back()) and (!b.elements[i])) {
        		out << "00000000";
        	}
        	out << b.elements[i];
        }
        return out;
    }
    friend istream &operator>>(istream &in, BigInteger &b) {
        string s;
        in >> s;
        if (s[0] == '-') {
            s.erase(s.begin());
            b.sign = true;
        }
        for (int i = s.length(); i > 0; i -= pow) {
            if (i < pow) {
                b.elements.push_back(stoi(s.substr(0, i)));
            } else {
				b.elements.push_back(stoi(s.substr(i - pow, pow)));
			}
        }
        return in;
    }
};
 
 
int main() {
    BigInteger a, b, c;
    cin >> a >> b;
    cout << a << " " << b <<'\n';
    cout << a - b  <<'\n';
    cout << a << " " << b <<'\n';
}
