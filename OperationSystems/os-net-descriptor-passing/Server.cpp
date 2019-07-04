#include <iostream>

#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>

const std::string SOCKET = "/tmp/socket";
const unsigned int BUFF_SIZE = 1024;

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
    if (unlink(SOCKET.data()) == -1 && errno != ENOENT)
    {
        std::cout << "Error occurred during unlink\n";
        return -1;
    }
    if (bind(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        std::cout << "Unable to bind to socket\n";
        return -1;
    }
    if (listen(sock, 5) == -1)
    {
        std::cout << "Unable to set listening for socket\n";
        return -1;
    }
    std::cout << "Server is up\n";
    while (true)
    {
        int client = accept(sock, nullptr, nullptr);
        if (client == -1)
        {
            std::cout << "Error during receiving request from client\n";
            exit(-1);
        }
        char ioBuf[BUFF_SIZE], buf[CMSG_SPACE(sizeof(int))] = {'\0'};
        struct iovec io = { .iov_base = &ioBuf, .iov_len = sizeof(ioBuf) };
        struct msghdr msg = {0};
        msg.msg_iov = &io; msg.msg_iovlen = 1;
        msg.msg_control = buf; msg.msg_controllen = sizeof(buf);
        struct cmsghdr *cmsg;
        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        if(sendmsg(client, &msg, 0) == -1)
        {
            std::cout << "Error occurred on sending message\n";
            exit(-1);
        }
    }
    if (close(sock) == -1)
    {
        std::cout << "Error occurred while closing the socket\n";
        return -1;
    }
    return 0;
}
