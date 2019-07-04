#include <fstream>
#include <iostream>


int main()
{
	std::ifstream inn;
    inn.open("planaritycheck.in");
	std::ifstream in;
    in.open("planaritycheck.out");
    std::ifstream in2;
    in2.open("planaritycheck2.out");
    int t, count = 0;
    inn >> t;
    std::string sn;
    getline(inn, sn);
    for (int i = 0; i < 33867; ++i)
    {
    	getline(inn, sn);
    	std::string s1, s2;
    	in >> s1;
    	in2 >> s2;
    	if (s1 != s2)
    	{
    		std::cout << i << ' ' << s1 << ' ' << s2 << ' ' << sn << '\n';
    		++count;
    	}
    }
    std::cout << count;
}
