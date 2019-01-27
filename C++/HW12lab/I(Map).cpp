#include <iostream>
#include <unordered_map>
#include <sstream>
 
int main()
{
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
    std::unordered_map <std::string, std::string> mp;
    std::string s, s1;
    std::stringstream stream;
    while (std::cin >> s >> s1)
    {
        if (s == "get")
        {
        	if (mp.count(s1))
            {
            	stream << mp[s1] << '\n';
            } else
            {
                stream << "none\n";
            }
        } else if (s == "put")
        {
            std::cin >> s;
            mp[s1] = s;
        } else if (s == "delete")
        {
            mp.erase(s1);
        }
    }
    std::cout << stream.str();
}
