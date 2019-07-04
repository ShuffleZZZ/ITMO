#include <string>
#include "Estonianator.h"

std::string estonianator(const std::string& input)
{
    std::string res = "";
    for (const char c : input)
    {
        if (c == 's')
        {
            res.append("š");
        } else if (c == 'z') {
            res.append("ž");
        } else if (c == 'o') {
            res.append("õ");
        } else if (c == 'a') {
            res.append("ä");
        } else if (c == 'u') {
            res.append("ü");
        } else if (c == 'S') {
            res.append("Š");
        } else if (c == 'Z') {
            res.append("Ž");
        } else if (c == 'O') {
            res.append("Õ");
        } else if (c == 'U') {
            res.append("Ü");
        } else {
            res += c;
        }
    }
    return res;
}
