#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    while(true)
    {
        std::cout << "~Kidshell: ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "" || std::cin.eof())
        {
            std::cout << "Terminating the program\n";
            break;
        }
        std::stringstream inputStream(input);
        std::vector <std::string> args;
        while (inputStream >> input)
        {
            args.push_back(input);
        }
        if (args.empty())
        {
            std::cout << "No arguments given, enter the correct input\n";
            continue;
        }
        std::vector <char*> argsPointers;
        for (std::string& i : args)
        {
              char* string = new char[i.size() + 1];
              strcpy(string, i.data());
              argsPointers.push_back(string);
        }
        argsPointers.push_back(nullptr);
        char** correctArgs = argsPointers.data();
        pid_t process = fork();
        if (process == -1)
        {
            std::cout << "Error on creating the child process\n";
        } else if (process == 0) {
            if (execve(correctArgs[0], correctArgs, envp) == -1)
            {
                std::cout << "Error occurred during the program execution\n";
                exit(-1);
            } else {
                exit(0);
            }
        } else {
            int status = 0;
            if (waitpid(process, &status, 0) == -1)
            {
                std::cout << "Error occurred while waiting for child process\n";
            } else {
                std::cout << "Program finished with return value: " << status << '\n';
            }
        }
        for (char*& i : argsPointers)
        {
            delete[] i;
        }
    }
    return 0;
}
