#include "../../header/utils/JSONFileManager.hpp"

JSONFileManager::JSONFileManager(std::string path)
{
    file_mPtr = std::make_shared<FileManager>(path, APPEND);
    if(file_mPtr->getFstream() == nullptr) {
        std::cerr<<"Error: File not found\n";
        return;
    }
    try{
        if(file_mPtr->getFileSize() > 2) {
            jsonArray = json::array();
            jsonArray = json::parse(*(file_mPtr->getFstream()));
        }
        else {
            jsonArray = json::array();
        }
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
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
    
    bool store_flag = file_mPtr->append(jsonArray.dump(4),0, true);
    
    return store_flag;
}

bool JSONFileManager::erase(int index)
{
    if(index < jsonArray.size()) {
        jsonArray.erase(index);
        file_mPtr->append(jsonArray.dump(4),0, true);
        return true;
    }
    return false;
}
int JSONFileManager::getFileSize() {

    return file_mPtr->getFileSize();
}