#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
const int base = 1000000000;
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
    static pair <int, int> add(int a, int b) {
    	if (a >= base - b) return {a - (base - b), 1};
    	return {a + b, 0};
	}
	static pair <int, int> multiply(int a, int b) {
        int ans = 0, carry = 0, overflow = 0;
        while (b) {
            if (b & 1) {
                pair<int, int> sum = add(ans, a);
                ans = sum.first;
                overflow += carry + sum.second;
            }
            pair<int, int> sum = add(a, a);
            a = sum.first;
            carry = (carry << 1) + sum.second;
            b >>= 1;
        }
        return {overflow, ans};
	}
    friend BigInteger operator*(BigInteger a, BigInteger b) {
        while (a.elements.size() < b.elements.size()) a.elements.push_back(0);
        while (b.elements.size() < a.elements.size()) b.elements.push_back(0);
        BigInteger res;
        res.sign = (a.sign != b.sign);
        res.elements.resize(2 * a.elements.size(), 0);
        for (int i = 0; i < a.elements.size(); ++i) {
        	int carry = 0;
        	for (int j = 0; (j < a.elements.size()) or carry; ++j) {
        		pair<int, int> temp = add(res.elements[i + j], carry);
        		if (j < a.elements.size()) {
        			pair<int, int> temp2 = multiply(a.elements[i], b.elements[j]);
        			pair<int, int> temp3 = add(temp.first, temp2.second);
        			res.elements[i + j] = temp3.first;
        			carry = temp.second + temp2.first + temp3.second;
        		} else {
        			res.elements[i + j] = temp.first;
        			carry = temp.second;
        		}
        		//cout << temp.second << ' ' << temp2.first << ' ' << temp3.second << "A " << temp3.first << '\n';
        		//cout << carry << ' ' << res.elements[i + j] << ' ' << i << ' ' << j << '\n';
        	}
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
    friend BigInteger operator*=(BigInteger &a, BigInteger b) {
        a = a * b;
        return a;
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
