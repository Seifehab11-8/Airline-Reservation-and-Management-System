#include "../header/utils/Date.hpp"
#include <iostream>
int main() {
    Date d1;
    // std::cin>>d1;
    d1.from_string("2034-12-23 6:49");
    std::cout<<d1;
    std::cout<<d1.to_string();
}