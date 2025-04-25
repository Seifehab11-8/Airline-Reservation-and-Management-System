//#include "../include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

// using json = nlohmann::json;

// void appendJsonObject(const std::string& filename, const json& newObject) {
//     std::fstream file(filename, std::ios::in | std::ios::out);
    
//     if (!file.is_open()) {
//         throw std::runtime_error("Cannot open file");
//     }

//     // Find the last bracket
//     file.seekg(-1, std::ios::end);
//     char lastChar;
//     file.get(lastChar);
//     std::cout<<lastChar;
    
//     if (lastChar != ']') {
//         throw std::runtime_error("Invalid JSON array format");
//     }

//     // Move cursor back to overwrite the closing bracket
    
//     // Add comma if not first element (check if file has more than just [])
//     file.seekg(0, std::ios::end);
//     // we know the size of the file from tellg how?
//     //!since tellg specify the position of pointer as offset from the bgeinning
//     // say you have a file of 3 bytes going to last position make tellg return 2 as its offset from ios_begin
//     if (file.tellg() > 2) {
//         file.seekp(-1, std::ios::end);
//         file << ",";
//     }
    
//     // Write the new object and close the array
//     file << newObject.dump() << "]";
//     file.close();
// }
class Person{
    public:
    int id = 23;
};

class Child: public Person{
};
void hello(std::shared_ptr<Person> p) {
    std::cout<<p.get()->id;
}

int main() {
    std::shared_ptr<Person> p = std::make_shared<Child>();
    hello(p);
    return 0;
}