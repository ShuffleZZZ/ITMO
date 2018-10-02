#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> to_base(int dig, int base) {
	std::vector<int> a;
	while (dig > 0) {
		a.push_back(dig % base);
		dig /= base;
	}
	return a;
}

std::string num_str(int a) {
	std::string ans;
	while (a) {
		ans = (char) (a % 10 + 48) + ans;
		a /= 10;
	}
	return ans;
}

int from_base(std::vector <int> a) {
	int ans = 0;
	for (int i = 0; i < a.size(); ++i) {
		ans += a[i] * pow(10, i);
	}
	return ans;	
}

int convert(int dig, int new_base = 2, int cur_base = 10) {
	if (new_base == cur_base) return dig;
	int res10 = 0;
	int temp = 0;
	while (dig) {
		res10 += (dig % 10) * pow(cur_base, temp++);
		dig /= 10;
	}
	if (new_base == 10) return res10;
	std::vector <int> ndig = to_base(res10, new_base);
	return from_base(ndig);
}

std::string convert(std::string dig, int new_base = 2, int cur_base = 10) {
	if (new_base == cur_base) return dig;
	int res10 = 0;
	int temp = 0;
	for (int i = dig.size() - 1; i >= 0; --i) {
		int tem = dig[i] - 48;
		tem *= pow(cur_base, temp++);
		res10 += tem;
	}
	std::string ans = num_str(res10);
	if (new_base == 10) return ans;
	std::vector <int> ndig = to_base(res10, new_base);
	return num_str(from_base(ndig));
}

int main() {
	int n, cur_base, deg;
	std::cin >> n >> cur_base >> deg;
	//string t = "101010";
	std::string t = "42";
	//cout << convert(t, deg, cur_base);
	std::cout << convert(n, deg, cur_base);
}
