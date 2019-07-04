#include <iostream>

#include <dlfcn.h>

#include "Swedishinator.h"
#include "Estonianator.h"

int main(int argc, char* argv[], char *envp[])
{
    if (argc < 2)
    {
        std::cout << "Wrong input: expected atleast 1 argument\n";
        return 0;
    }
    const char* dynamicLinkedLib = "libNorwegianator.so";
    void* linkedLib = dlopen(dynamicLinkedLib, RTLD_LAZY);
    if (linkedLib == nullptr)
    {
        std::cout << "Error occurred while loading linked lib" << '\n';
        return 0;
    }
    auto norwegianator = (std::string(*)(const std::string&)) dlsym(linkedLib, "norwegianator");
    if (norwegianator == nullptr)
    {
        std::cout << "Error occurred while loading function of linked lib" << '\n';
        dlclose(linkedLib);
        return 0;
    }
    std::cout << "Static lib (svenska):";
    for (size_t i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        std::cout << ' ' << swedishinator(input);
    }
    std::cout << "\nDynamic lib (eesti):";
    for (size_t i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        std::cout << ' ' << estonianator(input);
    }
    std::cout << "\nDynamic linked lib (norge):";
    for (size_t i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        std::cout << ' ' << norwegianator(input);
    }
    std::cout << '\n';
    dlclose(linkedLib);
    return 0;
}
