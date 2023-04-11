#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int child()
{
    int pid = fork();
    switch (pid) {
        case 0: 
          std::cout << "[child] I'm child." << std::endl;
          sleep(5);
          std::cout << "[child] I'm quit." << std::endl;
          break;
        case -1: 
          std::cout << "fork() failed." << std::endl;
          break;
        default: 
          std::cout << "[parent] I'm meself." << std::endl;
          std::cout << "[parent] I will wait child." << std::endl;
          wait(nullptr);
          std::cout << "[parent] I'm quit." << std::endl;
          break;
    }

    return pid;
}

int main(int argc, char *argv[])
{
    child();
    return 0;
}
