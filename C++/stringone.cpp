#include <iostream>
#include <cstring>

using namespace std;

template<size_t basic = 10>	
class BigInt {
private:
	char base;
	string num;
	bool sign;
public:
	BigInt() {
		base = basic +'0';
		num = "0";
		sign = 1;
	}
	
	BigInt(string s) {
		sign = 1;
		base = basic +'0';
		if (s[0] == '-') {
			sign = 0;
			s.erase(s.begin());
		} else if (s[0] == '+') {
			s.erase(s.begin());
		}
		num = s;
	}
	
	int Size() const {
		return num.size();
	}
	
	friend BigInt operator + (BigInt a, BigInt b) {
		BigInt c;
		c.base = a.base;
        if (a.sign == b.sign) {
            c.num = plus(a.num, b.num, c.base);
            c.sign = a.sign;
            return c;
        } else {
        	short temp = compare(a.num, b.num);
            if (temp == 1) {
                c.num = minus(a.num, b.num, c.base);
                c.sign = a.sign;
                return c;
            } else if (temp == -1) {
                c.num = minus(b.num, a.num, c.base);
                c.sign = b.sign;
                return c;
            } else {
            	c.num = "0";
            	c.sign = 1;
            	return c;
            }
        }
    }
    
    friend BigInt operator - (BigInt a, BigInt b) {
        BigInt c;
        c.base = a.base;
        short temp = compare(a.num, b.num);
        if (a.sign == b.sign) {
            if (temp == 1) {
                c.num = minus(a.num, b.num, c.base);
                c.sign = a.sign;
                return c;
            } else if (temp == -1) {
                c.num = minus(b.num, a.num, c.base);
                c.sign = !a.sign;
                return c;
            } else {
            	c.num = "0";
            	c.sign = 1;
            	return c;
            }
        } else {
            if (temp == 1) {
                c.num = plus(a.num, b.num, c.base);
                c.sign = a.sign;
                return c;
            } else if (temp == -1) {
                c.num = plus(a.num, b.num, c.base);
                c.sign = a.sign;
                return c;
            } else {
            	c.num = "0";
            	c.sign = 1;
            	return c;
            }
        }
    }
    
    friend BigInt operator * (BigInt a, BigInt b) {
    	BigInt c;
    	c.base = a.base;
    	c.num = multiply(a.num, b.num, a.base);
    	if (c.num == "0") c.sign = 1;
    	else c.sign = !(a.sign != b.sign);
    	return c;
    }
    
    friend BigInt operator += (BigInt &a, BigInt b) {
    	a = a + b;
        return a;
    }
    
    friend BigInt operator -= (BigInt &a, BigInt b) {
    	a = a - b;
        return a;
    }
    
    friend ostream &operator << (ostream &out, BigInt &b) {
        if (!b.sign) {
			out << '-';
		}
		out << b.num;
		return out;
    }
    
    friend istream &operator >> (istream &in, BigInt &b) {
        in >> b.num;
        b.sign = 1;
		if (b.num[0] == '-') {
			b.sign = 0;
			b.num.erase(b.num.begin());
		} else if (b.num[0] == '+') {
			b.num.erase(b.num.begin());
		}
        return in;
    }
private:
	static short compare (string a, string b) {
        if (a.size() > b.size()) return 1;
        if (a.size() < b.size()) return -1;
        for (unsigned i = 0; i < a.size(); ++i) {
			if (a[i] < b[i]) return -1;
			if (a[i] > b[i]) return 1;
		}
        return 0;
    }
    
	static string plus (string a, string b, char base) {
		while (a.size() < b.size()) a = '0' + a;
		while (b.size() < a.size()) b = '0' + b;
		char carry = '0';
		string res;
		res.resize(a.size());
		for (int i = a.size() - 1; i >= 0; --i) {
			res[i] = ((carry - '0') + (a[i] - '0') + (b[i] - '0')) + '0';
			if (res[i] >= base) {
				res[i] -= 10;
				carry = '1';
			} else carry = '0';
		}
		if (carry == '1') res = carry + res;
		return res;
	}
	
	static string minus (string a, string b, char base) {
	    while (a.size() < b.size()) a = '0' + a;
		while (b.size() < a.size()) b = '0' + b;
		string res;
		res.resize(a.size());
	    for (int i = a.size() - 1; i >= 0; --i) {
	        if (a[i] < b[i]) {
	            a[i] += base - '0';
	            --a[i - 1];
	        }
	        res[i] = ((a[i] - '0') - (b[i] - '0')) + '0';
	    }
	    while ((res[0] == '0') and (res.size() > 1)) res.erase(res.begin());
	    return res;
	}
	
	static string multiply (string a, string b, char base) {
	    if(a.size() > b.size()) return multiply(b, a, base);
	    string res = "0";
	    for(int i =a.size() - 1; i >= 0; --i) {
	        string temp;
	        temp.resize(b.size());
	        short carry = 0;
	        for(int j = b.size() - 1; j >= 0; --j) {
	            temp[j] = ((b[j] - '0') * (a[i] - '0')) + carry;
	            short lim = base - '0';
	            if (temp[j] >= lim) {
	                carry = (temp[j] / lim);
	                temp[j] -= (carry * lim);
	            } else carry = 0;
	            temp[j] += '0';
	        }
	        if (carry > 0) temp.insert(0, 1, (carry + '0'));
	        for (unsigned j = 0; j < a.size() - i - 1; ++j) temp += '0';
	        res = plus(res, temp, base);
	    }
	    while ((res[0] == '0') and (res.size() > 1)) res.erase(res.begin());
	    return res;
	}
};

int main() {
	BigInt <10> a, b;
	cin >> a >> b;
	//a -= b;
	BigInt <10> c = a * b;
	cout << c << ' ' << c.Size() << '\n';
}
	
