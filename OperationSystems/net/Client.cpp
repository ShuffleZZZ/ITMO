#include <iostream>
#include <cstring>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

const unsigned int BUFFER_SIZE = 1024, DEFAULT_PORT = 8080;

int getNumericValue(std::string value)
{
    bool error = 0;
    int result = 0;
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
        std::cout << "Wrong input: expected correct digit, not " << value << '\n';
        exit(0);
    }
    return result;
}

int main(int argc, char* argv[], char *envp[])
{
    if (argc != 3 && argc != 2)
    {
        std::cout << "Wrong input: \n";
        return 0;
    }
    int curSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (curSocket == -1)
    {
        std::cout << "Unable to create a socket\n";
        return -1;
    }
    int opt = 1;
    if (setsockopt(curSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::cout << "Unable to set socket's options\n";
        return -1;
    }
    int port = DEFAULT_PORT;
    char* message = argv[2];
    if (argc == 3)
    {
        port = getNumericValue(argv[1]);
    } else {
        message = argv[1];
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to connect client socket\n";
        return -1;
    }
    int responseSize = 0;
    while (responseSize < strlen(message))
    {
        int sended = send(curSocket, message + responseSize, strlen(message) - responseSize, 0);
        if (sended == -1)
        {
            std::cout << "Error occurred on sending the message\n";
            exit(-1);
        } else if (sended == 0) {
            break;
        }
        responseSize += sended;
    }
    std::cout << "Response for " << message << " is: ";
    char response[BUFFER_SIZE] = {};
    int requestSize = 0;
    while (requestSize < strlen(message))
    {
        int received = recv(curSocket, response, BUFFER_SIZE, 0);
        if (received == -1)
        {
            std::cout << "Error occurred while receiving a message\n";
            exit(-1);
        } else if (received == 0) {
            break;
        }
        requestSize += received;
        for (int i = 0; i < received; ++i)
        {
            std::cout << response[i];
        }
    }
    std::cout << '\n';
    if (close(curSocket) == -1)
    {
        std::cout << "Error occurred while closing the socket\n";
        return -1;
    }
    return 0;
}
