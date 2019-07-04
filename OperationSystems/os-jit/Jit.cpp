#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <sys/mman.h>
#include <unistd.h>

int factorial()
{
    int input = 0;
    int res = 1, temp = 1;
    while (--input > 0)
    {
        ++temp;
        res *= temp;
    }
    return res;
}

const unsigned short numPos = 7;

unsigned char hexCode[] = {
    0x55,
    0x48, 0x89, 0xe5,
    0xc7, 0x45, 0xf4, 0x00, 0x00, 0x00, 0x00,// last 4 hexes is number
    0xc7, 0x45, 0xf8, 0x01, 0x00, 0x00, 0x00,
    0xc7, 0x45, 0xfc, 0x01, 0x00, 0x00, 0x00,
    0x83, 0x6d, 0xf4, 0x01,
    0x83, 0x7d, 0xf4, 0x00,
    0x0f, 0x9f, 0xc0,
    0x84, 0xc0,
    0x74, 0x10,
    0x83, 0x45, 0xfc, 0x01,
    0x8b, 0x45, 0xf8,
    0x0f, 0xaf, 0x45, 0xfc,
    0x89, 0x45, 0xf8,
    0xeb, 0xe1,
    0x8b, 0x45, 0xf8,
    0x5d,
    0xc3
};

void getNumericValue(int& var, std::string& value)
{
    for (int i = 0; i < value.size(); ++i) {
        if (value[i] < 48 || value[i] > 57)
        {
            std::cout << "Wrong input: expected correct positive digit, not " << value << '\n';
            exit(0);
        }
        if (std::numeric_limits<int>::max() / 10 < var)
        {
            std::cout << "Wrong input: expected value not greater than integer\n";
            exit(0);
        }
        var *= 10;
        int lastDigit = value[i] - 48;
        if (std::numeric_limits<int>::max() - lastDigit < var)
        {
            std::cout << "Wrong input: expected value not greater than integer\n";
            exit(0);
        }
        var += lastDigit;
    }
}

int main(int argc, char* argv[], char *envp[])
{
    if (argc != 2 && argc != 1)
    {
        std::cout << "Wrong input: 0 or 1 arguments expected\n";
        return 0;
    }
    if (argc == 2)
    {
        int input = 0;
        std::string s = argv[1];
        getNumericValue(input, s);
        std::memcpy(hexCode + numPos, &input, 4);
    }
    void* funcMem = mmap(nullptr, sizeof(hexCode), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (funcMem == MAP_FAILED)
    {
        std::cout << "Memory assertion error\n";
        return -1;
    }
    unsigned short size = sizeof(hexCode) / sizeof(unsigned char);
    std::memcpy(funcMem, hexCode, size);
    if (mprotect(funcMem, size, PROT_READ | PROT_EXEC) == -1)
    {
        std::cout << "Unable to convert byte code to executable\n";
        return -1;
    }
    auto func = ((int(*)())funcMem)();
    std::string arg = argc == 2 ? argv[1] : "0";
    std::cout << "Factorial of " << arg << " is " << func << '\n';
    if (munmap(funcMem, size) == -1)
    {
        std::cout << "Memory unmapping error\n";
        return -1;
    }
    return 0;
}
