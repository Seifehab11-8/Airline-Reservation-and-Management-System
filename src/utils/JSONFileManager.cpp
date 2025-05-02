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
            jsonArray = json::parse(*(file_mPtr->getFstream().get()));
        }
        else {
            jsonArray = json::array();
        }
        file_mPtr->getFstream()->close();
        file_mPtr->getFstream()->open(path, OVERWRITE);
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
    std::cout<<jsonArray.dump(4);
    bool store_flag = file_mPtr->append(jsonArray.dump(4),0, true);
    
    return store_flag;
}

int JSONFileManager::getFileSize() {
    return file_mPtr->getFileSize();
}