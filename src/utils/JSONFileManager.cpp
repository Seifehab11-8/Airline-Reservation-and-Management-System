#include "../../header/utils/JSONFileManager.hpp"

JSONFileManager::JSONFileManager(std::string path)
{
    file_mPtr = std::make_shared<FileManager>(path, APPEND);
    jsonArray = json::parse(*(file_mPtr->getFstream()));
    file_mPtr->getFstream()->close();
    file_mPtr->getFstream()->open(path, OVERWRITE);
}
bool JSONFileManager::append(json jsonObj, int index)
{
    if(index == -1) {
        jsonArray.emplace_back(jsonObj);
    }
    else if (index < jsonArray.size()){
        auto it = jsonArray.begin() + index;
        jsonArray.insert(it , jsonObj);
    }
    file_mPtr->append(jsonArray.dump());
}

int JSONFileManager::getFileSize() {
    return file_mPtr->getFileSize();
}