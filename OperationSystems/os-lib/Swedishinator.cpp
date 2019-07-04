#include <string>
#include "Swedishinator.h"

std::string swedishinator(const std::string& input)
{
    std::string res = "";
    for (const char c : input)
    {
        if (c == 'a')
        {
            res.append("ä");
        } else if (c == 'o') {
            res.append("å");
        } else if (c == 'u') {
            res.append("ü");
        } else if (c == 'e') {
            res.append("ö");
        } else if (c == 'A') {
            res.append("Ä");
        } else if (c == 'O') {
            res.append("Å");
        } else if (c == 'U') {
            res.append("Ü");
        } else if (c == 'E') {
            res.append("Ö");
        } else {
            res += c;
        }
    }
    return res;
}
