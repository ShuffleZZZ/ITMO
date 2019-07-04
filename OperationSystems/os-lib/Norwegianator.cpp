#include <string>
#include "Norwegianator.h"

extern "C"
std::string norwegianator(const std::string& input)
{
    std::string res = "";
    for (const char c : input)
    {
        if (c == 'a')
        {
            res.append("æ");
        } else if (c == 'o') {
            res.append("å");
        } else if (c == 'e') {
            res.append("ø");
        } else if (c == 'A') {
            res.append("Æ");
        } else if (c == 'O') {
            res.append("Å");
        } else if (c == 'E') {
            res.append("Ø");
        } else {
            res += c;
        }
    }
    return res;
}
