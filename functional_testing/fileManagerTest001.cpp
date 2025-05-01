#include "../header/utils/FileManager.hpp"
#include <iostream>

int main() {
    FileManager f1("C:\\Users\\semaz\\OneDrive\\Documents\\Software_Development\\Airline-Reservation-and-Management-System\\functional_testing\\fileTest001.txt", OVERWRITE);
    f1.append("hello world how are you\n");
    f1.append("second data\n");
    f1.append("second data", 5);
    // std::string temp;
    // temp = f1.read(10, 5);
    // std::cout<<temp <<std::endl;
    // do{
    //     temp = f1.read();
    //     std::cout<<temp <<std::endl;
    // }while(temp.empty() == false);
    std::cout<<"this is the file size: " <<f1.getFileSize()<<std::endl;
}