#include "../include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
int main() {
    std::ifstream inputFile("C:\\Users\\semaz\\OneDrive\\Documents\\Software_Development\\Airline-Reservation-and-Management-System\\storage\\test1.json");
    json j = json::parse(inputFile).at(1);
    json jn = {{"name", "ahmed"}};
    // j.push_back(jn);
    std::cout<<j["name"]<<std::endl;
    std::cout<<j["id"]<<std::endl;
    // for(auto n: j) {
    //     std::cout<<n.dump(4);
    //     // std::cout<<std::endl;
    // }
    std::ofstream outputFile("../storage/out.json");
    outputFile << jn;
}