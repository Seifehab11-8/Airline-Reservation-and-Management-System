#ifndef _FILE_MANAGER_HPP
#define _FILE_MANAGER_HPP
#include <fstream>
#include <filesystem>
#include <string>
#include <memory>

using File_ptr = std::shared_ptr<std::fstream>;
static constexpr std::ios_base::openmode APPEND = (std::ios_base::out | std::ios_base::in);
static constexpr std::ios_base::openmode OVERWRITE = (std::ios_base::out | std::ios_base::in | std::ios_base::trunc);

class FileManager {
    private:
    std::string path;
    File_ptr f_ptr;
    public:
    FileManager(std::string path, std::ios_base::openmode mode);
    FileManager() = delete;
    FileManager(const FileManager &other) = default;
    FileManager(FileManager && other) = default;
    virtual ~FileManager();
    bool append(std::string text, int offset = 0);
    int getFileSize();
    File_ptr getFstream();
};
#endif // !_FILE_MANAGER_HPP