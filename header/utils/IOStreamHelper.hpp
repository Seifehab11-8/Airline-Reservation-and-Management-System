#ifndef _IO_STREAM_HELPER_HPP 
#define _IO_STREAM_HELPER_HPP
#include <iostream>
class IOStreamHelper {
    public:
    static int InputNumeric();
};

// Utility function to clear buffer only if next char is '\n'
inline void clearInputBufferIfNewline(std::istream& is = std::cin) {
    if (is.peek() == '\n') {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

#endif // !