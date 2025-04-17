#include <../include/nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;
int main() {
    json j = {
        {"name", "Seifalla Ehab Mohamed"},
        {"ID", 2100619},
        {"email", "semaziz2003@gmail.com"}
    };
    std::cout<<j.dump(4);
}