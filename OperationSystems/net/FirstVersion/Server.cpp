#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

const unsigned int BUFFER_SIZE = 1024, DEFAULT_PORT = 8080;
const char* TERMINATION_STRING = "Good bye\n";

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
    if (argc > 2)
    {
        std::cout << "Wrong input: just port expected\n";
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
    if (argc == 2)
    {
        port = getNumericValue(argv[1]);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to bind to socket\n";
        return -1;
    }
    if (listen(curSocket, 1) == -1)
    {
        std::cout << "Unable to set listening for socket\n";
        return -1;
    };
    while (true)
    {
        int client = accept(curSocket, nullptr, nullptr);
        if (client == -1)
        {
            std::cout << "Error during receiving request from client\n";
            continue;
        }
        char request[BUFFER_SIZE] = {};
        int requestSize = recv(client, request, BUFFER_SIZE, 0);
        if (requestSize == -1)
        {
            std::cout << "Error occurred while receiving a message\n";
            continue;
        }
        if (strncmp(request, "shutdown", requestSize) == 0)
        {
            if (send(client, TERMINATION_STRING, strlen(TERMINATION_STRING), 0) == -1)
            {
                std::cout << "Error occurred on sending the message\n";
            }
            if (close(client) == -1)
            {
                std::cout << "Error occurred while closing the client socket\n";
                return -1;
            }
            std::cout << "Server has been shut down by client\n";
            break;
        }
        for (int i = 0; i < requestSize / 2; ++i)
        {
            char temp = request[i];
            request[i] = request[requestSize - 1 - i];
            request[requestSize - 1 - i] = temp;
        }
        if (send(client, request, requestSize, 0) == -1)
        {
            std::cout << "Error occurred on sending the message\n";
        }
    }
    if (close(curSocket) == -1)
    {
        std::cout << "Error occurred while closing the socket\n";
        return -1;
    }
    return 0;
}
