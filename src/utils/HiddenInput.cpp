#include <iostream>
#include <string>
#include "../../header/utils/HiddenInput.hpp"
#if defined(_WIN32)
#include <conio.h>
std::string getInput() {
    std::string password;
    char c;
    while ((c = _getch()) != '\r') {
        if (c == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password += c;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
#else
#include <termios.h>
#include <unistd.h>
std::string HiddenInput::getInput() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    char c;
    while (std::cin.get(c) && c != '\n') {
        if (c == 127 || c == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password += c;
            std::cout << '*';
            std::cout.flush();
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return password;
}
#endif