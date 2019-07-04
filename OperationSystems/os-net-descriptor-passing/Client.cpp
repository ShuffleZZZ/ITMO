#include <iostream>

#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>

const std::string SOCKET = "/tmp/socket";
const unsigned int BUFF_SIZE = 1024;

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
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cout << "Unable to create a socket\n";
        return -1;
    }
    struct sockaddr_un addr {};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET.data(), sizeof(addr.sun_path) - 1);
    if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        std::cout << "Unable to connect to socket\n";
        return -1;
    }
    int id = 0;
    if (argc > 1)
    {
        id = getNumericValue(argv[1]);
    }
    char ioBuf[BUFF_SIZE], buf[CMSG_SPACE(sizeof(int))] = {'\0'};
    struct iovec io = { .iov_base = &ioBuf, .iov_len = sizeof(ioBuf) };
    struct msghdr msg = {0};
    msg.msg_iov = &io; msg.msg_iovlen = 1;
    msg.msg_control = buf; msg.msg_controllen = sizeof(buf);
    if (recvmsg(sock, &msg, 0) == -1)
    {
        std::cout << "Error occurred on receiving the message\n";
        exit(-1);
    }
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    dup2(*((int*)CMSG_DATA(cmsg)), 1);
    while (true)
    {
        char buffer[BUFF_SIZE] = {};
        std::cin >> buffer;
        if (strncmp(buffer, "exit", 4) == 0)
        {
            std::cout << "Client" << id << " exited\n";
            break;
        } else {
            std::cout << "Client" << id << ": " << buffer << '\n';
        }
    }
    if (close(sock) == -1)
    {
        std::cout << "Error occurred while closing the socket\n";
        return -1;
    }
    return 0;
}
