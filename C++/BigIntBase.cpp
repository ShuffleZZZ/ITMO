#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template<typename T, int Base = std::numeric_limits<T>::max(), int pow = std::numeric_limits<T>::digits - 1>
class BigInteger {
private:
    vector<T> elements;
    int size = 0;
    bool sign = false;
	explicit operator BigInteger<T, Base>();
	int Size() const {
		return size;
	};
	T operator[](int id) const {
		int temp = pow;
		while (id > temp) {
			temp += pow;
		}
		id -= temp;
		return elements[temp] / (10 * (id - 1) % 10);
	}
	void set (BigInteger a, BigInteger b) {
		for (int i = 0; i < a.Size() / pow; ++i) {
			int temp = 1;
			int res = 0;
			for (int j = 0; j < pow; ++j) {
				res += b[j] * temp;
				temp *= 10;
			}
			a.elements[i] = res;
		}
		for (int i = a.Size() / pow; i < 
    static int compare(BigInteger a, BigInteger b) {
        if (a.Size() > b.Size())
            return 1;
        if (a.Size() < b.Size())
            return 0;
        for (int i = a.Size(); i >= 0; i--){
			if (a[i] < b[i])
				return 0;
			if (a[i] > b[i]) 
				return 1;
		}
        return 2;
    }
    static BigInteger plus (BigInteger a, BigInteger b) {
    	bool left;
    	for (int i = 0; i <= min(a.Size(), b.Size()); ++i) {
    		a[i] += b[i];
    		left = (a[i] > Base - 1);
    		if ((left) and (i != a.Size())) {
    			a[i]-= Base;
    			++a[i + 1];
    		}
    	}
    	if ((a.Size() <= b.Size()) and (left)) {
    		a.elements.push_back(1);
    	}
    	return a;
    }
    /*static BigInteger plus (BigInteger a, BigInteger b) {
        int left = 0;
        for (unsigned i = 0; i < max(a.elements.size(), b.elements.size()) or left; i++) {
            if (i == a.elements.size())
                a.elements.push_back(0);
           	a.elements[i] += left;
            if (i < b.elements.size()) 
            	a.elements[i] +=b.elements[i];
            left = (a.elements[i] >= Base);//NEW
            if (left)
				a.elements[i] -= Base;//NEW
        }
        return a;
    }*/
    static BigInteger minus (BigInteger a, BigInteger b) {
    	bool left;
    	for (int i = 0; i <= b.Size(); ++i) {
    		a[i] -= b[i];
    		left = (a[i] < 0);
    		if (left) {
    			a[i] += Base;
    			int temp = i + 1;
    			while (a[temp] <=0) {
    				++temp;
    			}
    			--a[temp];
    			for (int j = i + 1; j < temp; ++j) {
    				a[j] = Base - 1;//doesnt work properply
    			}
    		}
    	}
    	return a;
    }
    /*static BigInteger minus (BigInteger a, BigInteger b) {
        int left = 0;
        for (unsigned i = 0; i < b.elements.size() or left; i++) {
        	if (i < b.elements.size())
        		a.elements[i] -= left + b.elements[i];
        	else
        		a.elements[i] -= left;
            left = (a.elements[i] < 0);
            if (left)
				a.elements[i] += Base; //NEW
        }
        while ((a.elements.size() > 1) and (a.elements.back() == 0))
            a.elements.pop_back();
        return a;
    }*/
    friend BigInteger operator+(BigInteger a, BigInteger b) {
        BigInteger c;
        int temp = compare(a, b);
        if (a.sign == b.sign) {
        	if (!temp) c = plus(b, a); else c = plus(a, b);
            c.sign = a.sign;
            return c;
        } else {
            if (temp == 1) {
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
        int temp = compare(a, b);
        if (a.sign == b.sign) {
            if (temp == 1) {
                c = minus(a, b);
                c.sign = a.sign;
                return c;
            } else if (temp == 0) {
                c = minus(b, a);
                c.sign = !a.sign;
                return c;
            } else {
            	c = minus(b, a);
            	c.sign = false;
            	return c;
            }
        } else {
            if (temp == 1) {
                c = plus(a, b);
                c.sign = a.sign;
                return c;
            } else if (temp == 0) {
                c = plus(b, a);
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
        if (b.sign) out << '-';
        for (int i = b.Size(); i >= 0; i--) {
        	out << b[i];
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
            	int temp = stoi(s.substr(0, i));
                b.elements.push_back(temp);
                int cur = pow;
                while (!((1 << cur) | temp)) {
                	--cur;
                }
                b.size += cur;
            }else {
				b.elements.push_back(stoi(s.substr(i - pow, pow)));
				b.size += pow;
			}
		}
        return in;
    }
};

int main() {
	BigInteger<int, 6> a;
	BigInteger<int, 6> b;
	BigInteger<int, 6> c;
	cin >> a >> b;
	c = a - b;
}
