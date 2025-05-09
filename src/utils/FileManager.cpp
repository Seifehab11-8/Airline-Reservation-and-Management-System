#include "../../header/utils/FileManager.hpp"
#include <iostream>
#include <fstream>

FileManager::FileManager(std::string path, std::ios_base::openmode mode)
    : path(std::move(path))
{
    f_ptr = std::make_shared<std::fstream>(this->path, mode);
    if (!f_ptr->is_open()) {
        f_ptr = nullptr;
        std::cerr << "Failed to open file: " << this->path << std::endl;
    }
}

FileManager::~FileManager()
{
    if (f_ptr && f_ptr->is_open()) {
        f_ptr->close();
    }
}

bool FileManager::append(std::string text, int offset, bool overwriteFlag)
{
    if (!f_ptr || !f_ptr->is_open()) return false;

    // If overwriteFlag is true, truncate the file and write from the beginning
    if (overwriteFlag) {
        f_ptr->close();
        f_ptr->open(path, std::ios::out | std::ios::trunc);
        if (!f_ptr->is_open()) {
            std::cerr << "Failed to open file for overwriting: " << path << std::endl;
            return false;
        }
        (*f_ptr) << text;
        f_ptr->flush();
        f_ptr->close();
        // Reopen in original mode for further operations
        f_ptr->open(path, std::ios::in | std::ios::out);
        std::cout << "File " << path << " has been successfully overwritten\n";
        return true;
    }

    // Otherwise, append at the end or at the given offset
    if (offset > 0) {
        f_ptr->seekp(offset, std::ios_base::beg);
    } else {
        f_ptr->seekp(0, std::ios_base::end);
    }
    (*f_ptr) << text;
    f_ptr->flush();
    std::cout << "File " << path << " has been successfully updated\n";
    return true;
}

int FileManager::getFileSize()
{
    if (!f_ptr || !f_ptr->is_open()) return 0;
    auto current = f_ptr->tellg();
    f_ptr->seekg(0, std::ios_base::end);
    int size = static_cast<int>(f_ptr->tellg());
    f_ptr->seekg(current, std::ios_base::beg);
    return size;
}

File_ptr FileManager::getFstream()
{
    return f_ptr;
}
