#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

std::string K33[10] = {"000111111011100", "011001110111010", "011110001111001", "011110110000111", //123 124 125 126
"101010101110110", "101101010110101", "101101101001011", //134 135 136
"110011011010011", "110011100101101", //145 146
"110100011101110"}; //156
 
int main()
{
    std::ifstream in;
    in.open("planaritycheck.in");
    std::ofstream out;
    out.open("planaritycheck.out");
    int t;
    in >> t;
    std::string s;
    getline(in, s);
    for (int i = 0; i < t; ++i)
    {
        getline(in, s);
        int n = 0;
        switch (s.size())
        {
        	case 15:
        		n = 6;
        		break;
        	case 10:
        		n = 5;
        		break;
        }
        if (n < 5)
        {
            out << "YES" << '\n';
        } else if (n == 5)
        {
            if (s.compare("1111111111"))
            {
                out << "YES" << '\n';
            } else
            {
                out << "NO" << '\n';
            }
        } else
        {
            bool a[n][n] = {};
            int d[n] = {};
            bool ans = 0;
            int ind = 0;
            for (int j = 1; j < n; ++j)
            {
                for (int k = 0; k < j; ++k)
                {
                    if (s[ind++] == '1')
                    {
                        a[j][k] = a[k][j] = 1;
                        ++d[j];
                        ++d[k];
                    }
                }
            }
            std::vector <int> vertex;
            for (int j = 0; j < n; ++j)
            {
            	vertex.push_back(d[j]);
                std::vector <int> deg;
                for (int k = 0; k < n; ++k)
                {
                    if (k != j)
                    {
                    	if (a[k][j])
                    	{
                        	deg.push_back(d[k] - 1);
                        } else
                        {
                        	deg.push_back(d[k]);
                        }
                    }
                }
                bool ans_j = 1;
                for (int k = 0; k < deg.size(); ++k)
                {
                    if (deg[k] != n - 2)
                    {
                        ans_j = 0;
                        break;
                    }
                }
                ans |= ans_j;
            }
            if (ans)
            {
            	out << "NO" << '\n';
            } else
            {
				for (int j = 0; j < 10; ++j)
	            {
	                bool ans_j = 1;
	                for (int k = 0; k < K33[j].size(); ++k)
	                {
	                    if (K33[j][k] == '1' && s[k] == '0')
	                    {
	                        ans_j = 0;
	                        break;
	                    }
	                }
	                ans |= ans_j;
	            }
	            if (ans)
	            {
	                out << "NO" << '\n';
	            } else
	            {
					std::sort(vertex.begin(), vertex.end());
					if (vertex[0] == 2 && vertex[1] == 4 && vertex[2] == 4 && vertex[3] == 4 && vertex[4] == 4)
					{
						out << "NO" << '\n';
					} else
					{
	                	out << "YES" << '\n';
	                }
	            }
	        }
        }
    }
    in.close();
    out.close();
}
