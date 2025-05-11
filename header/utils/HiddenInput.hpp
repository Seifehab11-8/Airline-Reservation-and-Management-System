#ifndef HIDDEN_INPUT_HPP
#define HIDDEN_INPUT_HPP

#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #define HIDDENINPUT_WINDOWS
    #include <conio.h>
#else
    #define HIDDENINPUT_UNIX
    #include <termios.h>
    #include <unistd.h>
#endif

class HiddenInput {
public:
    HiddenInput() = default;
    HiddenInput(const HiddenInput &other) = default;
    HiddenInput(HiddenInput && other) = default;
    static std::string getInput();
};

#endif