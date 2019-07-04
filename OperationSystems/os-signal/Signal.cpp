#include <iostream>
#include <cstring>
#include <climits>

#include <csignal>
#include <csetjmp>
#include <unistd.h>

const int MEMORY_DUMP_RANGE = 20;
const char* regStr[23] = {"R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15",
"RDI", "RSI", "RBP", "RBX", "RDX", "RAX", "RCX", "RSP", "RIP", "EFL", "CSGSFS",
"ERR", "TRAPNO", "OLDMASK", "CR2"};

static jmp_buf jmpBuf;


void print(const char* string)
{
    write(1, string, strlen(string));
}

void printNum(long long num)
{
    if (num)
    {
        printNum(num >> 4);
        char symbol = num & 15;
        if (symbol < 10)
        {
            symbol += '0';
        } else {
            symbol += 'a' - 10;
        }
        write(1, &symbol, 1);
    }
}

void print(long long num)
{
    if (num)
    {
        printNum(num);
    } else {
        print("0");
    }
}

void sigsegvAddressHandler(int num, siginfo_t* siginfo, void* context)
{
    if (siginfo -> si_signo == SIGSEGV)
    {
        siglongjmp(jmpBuf, 1);
    }
}

void dumpReg(ucontext_t* context)
{
    print("Registers dump \n");
    for (size_t reg = 0; reg < NGREG; ++reg)
    {
        print(regStr[reg]);
        print(": 0x");
        print(context->uc_mcontext.gregs[reg]);
        print("\n");
    }
}

void dumpMem(void* address)
{
    print("Memory dump \n");
    long long shift = (long long)((char*) address - MEMORY_DUMP_RANGE);
    long long from = 0;
    if (shift > 0)
    {
        from = shift;
    }
    shift += MEMORY_DUMP_RANGE;
    long long to = LONG_LONG_MAX;
    if (shift < LONG_LONG_MAX - MEMORY_DUMP_RANGE)
    {
        to = shift + MEMORY_DUMP_RANGE;
    }
    for (long long i = from; i < to; ++i)
    {
        sigset_t setSignal;
        sigemptyset(&setSignal);
        sigaddset(&setSignal, SIGSEGV);
        sigprocmask(SIG_UNBLOCK, &setSignal, nullptr);
        struct sigaction sAction {};
        sAction.sa_sigaction = sigsegvAddressHandler;
        sAction.sa_flags = SA_SIGINFO;
        if (sigaction(SIGSEGV, &sAction, nullptr) == -1)
        {
            print("Error occurred during sigaction\n");
            _exit(-1);
        }
        print("0x");
        print(i);
        print(" ");
        if (setjmp(jmpBuf) != 0)
        {
            print("failed to dump\n");
        } else {
            print((int)((const char*)i)[0]);
            print("\n");
        }
    }
}

void sigsegvHandler(int num, siginfo_t* siginfo, void* context)
{
    if (siginfo -> si_signo == SIGSEGV)
    {
        print("Signal rejected: ");
        print((const char*) strsignal(num));
        print("\n");
        if (siginfo -> si_code == SEGV_MAPERR)
        {
            print("Reason: nothing is mapped to address\n");
        } else if(siginfo -> si_code == SEGV_ACCERR) {
            print("Reason: access error\n");
        } else {
            print("Error code: ");
            print(siginfo -> si_code);
            print("\n");
        }
        print("Address: ");
        if(siginfo -> si_addr == nullptr)
        {
            print("nullptr. No memory dump needed\n");
        } else {
            print("0x");
            print((intptr_t) siginfo -> si_addr);
            print("\n");
        }
        dumpReg((ucontext_t*) context);
        if (siginfo -> si_addr != nullptr)
        {
            dumpMem(siginfo -> si_addr);
        }
    }
    _exit(1);
}

int main(int argc, char* argv[], char *envp[])
{
    struct sigaction action {};
    action.sa_sigaction = sigsegvHandler;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGSEGV, &action, nullptr) == -1)
    {
        std::cout << "Error occurred during sigaction\n";
        return -1;
    }
    std::cout << "Choose one of the options: \n";
    std::cout << "1. Left-bound test\n2. Right-bound test\n3. nullptr test\n";
    unsigned short ans = 0;
    std::cin >> ans;
    if (ans == 1)
    {
        char* test = (char*) "check";
        *(--test) = 'A';
    } else if (ans == 2) {
        char* test = (char*) "check";
        test[6] = '1';
    } else if (ans == 3) {
        unsigned short* test = nullptr;
        *test = 1;
    } else {
        std::cout << "Incorrect input: expected number of option\n";
    }
    return 0;
}
