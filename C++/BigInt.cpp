#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
const unsigned base = 1000000000;
const int pow = 9;

class BigInteger {
private:
    vector<unsigned> elements;
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
    /*static vector<int> baseshuffle(vector<int> &a, int old, int need) {
        vector<long long> p(max(old, need) + 1);
        p[0] = 1;
        for (int i = 1; i < p.size(); ++i) p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int curd = 0;
        for (int i = 0; i < a.size(); ++i) {
            cur += a[i] * p[curd];
            curd += old;
            while (curd >= need) {
                res.push_back(cur % p[need]);
                cur /= p[need];
                curd -= need;
            }
        }
        res.push_back(cur);
        while ((!res.empty()) and (!res.back())) res.pop_back();
        return res;
    }*/
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
    friend BigInteger operator*(BigInteger a, BigInteger b) {
        while (a.elements.size() < b.elements.size()) a.elements.push_back(0);
        while (b.elements.size() < a.elements.size()) b.elements.push_back(0);
        vector<unsigned long long> c(2 * a.elements.size());
        for (int i = 0; i < a.elements.size(); ++i)
            for (int j = 0; j < a.elements.size(); ++j)
				c[i + j] +=(unsigned long long) a.elements[i] * b.elements[j];
        BigInteger res;
        res.sign = (a.sign != b.sign);
        for (int i = 0, carry = 0; i < c.size(); ++i) {
            unsigned long long cur = c[i] + carry;
            res.elements.push_back(cur % base);
            carry = cur / base;
        }
        while ((!res.elements.empty()) and (!res.elements.back())) res.elements.pop_back();
        if (res.elements.empty()) res.sign = 0;
        return res;
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
		if (b.elements.empty()) out << 0;
		else out << b.elements.back();
        for (int i = b.elements.size() - 2; i >= 0; --i) {
        	out << setw(pow) << setfill('0') << b.elements[i];
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
    /*cout << a << " " << b <<'\n';
    cout << a - b  <<'\n';
    cout << a << " " << b <<'\n';*/
    cout << a << ' ' << b << '\n';
    cout << a * b << '\n';
    cout << a << ' ' << b << '\n';
}
