#include "../../header/utils/FileManager.hpp"
#include <iostream>

FileManager::FileManager(std::string path, std::ios_base::openmode mode)
{
    this->path = path;
    f_ptr = std::make_shared<std::fstream>(path, mode);
    if(f_ptr->is_open() == false) {
        f_ptr = nullptr;
    }
}

FileManager::~FileManager()
{
    f_ptr->close();
}

bool FileManager::append(std::string text, int offset, bool overwriteFlag)
{
    
    if(f_ptr != nullptr) {
        if(offset <= 0 && overwriteFlag == false) {
            f_ptr->seekp(offset, std::ios_base::end);
        }
        else if(offset >= 0 && overwriteFlag == true) {
            f_ptr->seekp(offset, std::ios_base::beg);
        }
        (*f_ptr) << text;
        return true;
    }
    return false;
}


int FileManager::getFileSize()
{
    if(f_ptr == nullptr) return 0;
    int current = (static_cast<int>(f_ptr->tellg()));
    f_ptr->seekg(0, std::ios_base::end);
    int size  = (static_cast<int>(f_ptr->tellg()) + 1);
    f_ptr->seekg(current, std::ios_base::beg);
    return size;
}

File_ptr FileManager::getFstream()
{
    return f_ptr;
}
