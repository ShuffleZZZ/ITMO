#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

stack <double> calc;

void Sum(int k)
{
    if (calc.size() > 1)
    {
        for (int i = 0; i < k - 1; i++)
        {
            double tmp1, tmp2;
            tmp2 = calc.top();
            calc.pop();
            tmp1 = calc.top();
            calc.pop();
            calc.push((tmp1 + tmp2));
        }
    }
}

int Chstn()
{
    if (calc.size() > 1)
    {
        double tmp1, tmp2;
        tmp2 = calc.top();
        if (tmp2 == 0)
        {
            cout << "Ошибка! Делить на 0 нельзя!" << '\n';
            system("pause");
            return -1;
        }
        else
        {
            calc.pop();
            tmp1 = calc.top();
            calc.pop();
            calc.push(tmp1/tmp2);
        }
    }
}

void Przv(int k)
{
    if (calc.size() > 1)
    {
        for (int i = 0; i < k - 1; i++)
        {
            double tmp1, tmp2;
            tmp2 = calc.top();
            calc.pop();
            tmp1 = calc.top();
            calc.pop();
            calc.push((tmp1 * tmp2));
        }
    }
}

void Rzn()
{
    if (calc.size() > 1)
    {
        double tmp1, tmp2;
        tmp2 = calc.top();
        calc.pop();
        tmp1 = calc.top();
        calc.pop();
        calc.push((tmp1 - tmp2));
    }
}

void Pw()
{
    if (calc.size() > 0)
    {
        double tmp1, tmp3;
        int tmp2 = calc.top();
        calc.pop();
        tmp1 = calc.top();
        calc.pop();
        tmp3 = pow(tmp1, tmp2);
        calc.push(tmp3);
    }
}

int main(int argc, char* argv[])
{
    int k;
    k = 2;
    setlocale(LC_ALL,"Russian" );
    cout.precision(2);
    for (int i = 1; i < argc; i++)
    {
        string op = argv[i];
        if (op == "+")
        {
            Sum(k);
            continue;
        }
        else if (op == "x")
        {
            Przv(k);
            continue;
        }
        else if (op == "-")
        {
            Rzn();
            continue;
        }
        else if (op == "pow")
        {
            Pw();
            continue;
        }
        else if (op == "/" && calc.size() > 1)
        {
            int check = Chstn();
            if (check == -1)
                return 0;
            else
                continue;
        }
        else
        {
            string s = argv[i];
            double x = 0;
            int i = 0;
            while (s[i] != '.' && s[i] != ',' && i < s.size())
            {
                i++;
            }
            int k = i;
            int k1 = -1;
            for (int j = k + 1; j < s.size(); j++)
            {
                x += (s[j] - '0') * pow(10, k1);
                k1--;
            }
            k1 = 0;
            for (int j = k - 1; j >= 0; j--, k1++)
            {
                x += (s[j] - '0') * pow(10, k1);
            }
            calc.push(x);
            continue;
        }

    }
    if (calc.empty())
        cout << "Стек ответа пуст" << '\n';
    else
    {
        cout << "Ответ:" << '\n';
        cout << calc.top() << '\n';
    }
    system("pause");
    return 0;
}

