#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>

#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

std::vector <char*> argsPointers(1);
unsigned short visitedMask = 0;
std::string name, program;
nlink_t nlink;
off_t size;
char sizeState;
ino_t inum;
std::vector <std::string> files;

template <typename T>
void getNumericValue(T& var, std::string& value)
{
    char sign = '+';
    if (value[0] == '+' || value[0] == '-')
    {
        sign = value[0];
        value.erase(value.begin());
    }
    bool error = 0;
    size_t result = 0;
    for (char c : value) {
        if (c < 48 || c > 57)
        {
            error = 1;
            break;
        }
        result *= 10;
        result += c - 48;
    }
    if (error)
    {
        std::cout << "Wrong input: expected correct digit, not "
        << sign << value << '\n';
        exit(0);
    }
    var = static_cast <T>(result);
}

void isNeeded(std::string& file_path, std::string& file_name)
{
    struct stat buf{};
    if (lstat(file_path.data(), &buf) == -1)
    {
        std::cout << "Wrong input: illigal path\n";
        exit(0);
    }
    if ((!(visitedMask & 1) || buf.st_ino == inum) &&
        (!(visitedMask & 4) || buf.st_nlink == nlink) &&
        (!(visitedMask & 16)|| file_name == name) &&
        (!(visitedMask & 2) ||
         (sizeState == 0 && buf.st_size < size) ||
         (sizeState == 1 && buf.st_size == size) ||
         (sizeState == 2 && buf.st_size > size)))
    {
                files.emplace_back(file_path);
    }
}

void find(std::string path)
{
    if (path[path.size() - 1] != '/' || path[path.size() - 1] != '\\')
    {
        path += '/';
    }
    DIR* dir = opendir(path.data());
    if (dir == nullptr)
    {
        if (errno != EACCES)
        {
            std::cout << "Unable to open directory: " << path.data() << '\n';
            return;
        } else {
            return;
        }
    }
    while (true)
    {
        dirent* reader = readdir(dir);
        if (reader == nullptr)
        {
            break;
        }
        std::string dirCheck = reader -> d_name;
        std::string absPath = path + dirCheck;
        if (dirCheck == "." || dirCheck == "..")
        {
            continue;
        }
        isNeeded(absPath, dirCheck);
        if (reader -> d_type == DT_DIR)
        {
            find(absPath);
        }
    }
    if (closedir(dir) == -1)
    {
        std::cout << "Unable to close directory\n";
        exit(0);
    }
}

int main(int argc, char* argv[], char *envp[])
{
    if (argc < 2)
    {
        std::cout << "Wrong input\n";
        return 0;
    }
    std::string path = argv[1];
    argsPointers[0] = nullptr;
    for (int i = 2; i < argc - 1; i += 2)
    {
        std::string flag = argv[i], value = argv[i + 1];
        if (flag == "-inum")
        {
            getNumericValue(inum, value);
            visitedMask |= 1;
        } else if (flag == "-size") {
            if (value[0] == '-') {
                sizeState = 0;
            } else if (value[0] == '=') {
                sizeState = 1;
            } else if (value[0] == '+') {
                sizeState = 2;
            } else {
                std::cout << "Wrong input: incorrect size value\n";
                return 0;
            }
            getNumericValue(size, value);
            visitedMask |= 2;
        } else if (flag == "-nlinks") {
            getNumericValue(nlink, value);
            visitedMask |= 4;
        } else if (flag == "-exec") {
            char* string = new char[value.size() + 1];
            strcpy(string, value.data());
            argsPointers[0] = string;
            visitedMask |= 8;
        } else if (flag == "-name") {
            name = value;
            visitedMask |= 16;
        } else {
            std::cout << "Wrong input: illigal arguments\n";
            return 0;
        }
    }
    struct stat buf{};
    if (stat(argv[1], &buf) == -1)
    {
        std::cout << "Wrong input: illigal path\n";
    } else if (buf.st_mode & S_IFREG) {
        std::string file;
        for (char c : path)
        {
            if (c == '/' || c == '\\')
            {
                file.clear();
            } else {
                file += c;
            }
        }
        isNeeded(path, file);
    } else {
        find(path);
    }
    if (argsPointers[0] != nullptr)
    {
        for (std::string& i : files)
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
    } else {
        for (std::string& i : files)
        {
            std::cout << i.data() << '\n';
        }
    }
    return 0;
}
