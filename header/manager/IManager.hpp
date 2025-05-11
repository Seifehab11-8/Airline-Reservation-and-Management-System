#ifndef _I_MANAGER_HPP
#define _I_MANAGER_HPP 

#include "../utils/JSONFileManager.hpp"
#include <string>
class IManager {
    public:
    IManager() = default;
    IManager(const IManager &other) = default;
    IManager(IManager && other) = default;
    virtual void create() = 0;
    virtual void update() = 0;
    virtual void _delete() = 0;
    virtual void view() = 0;
    template<typename type> 
    int exist(const type& element, Json_file_ptr file_access_ptr);
};

template <typename type>
inline int IManager::exist(const type &element, Json_file_ptr file_access_ptr)
{
    std::vector<type> listOfElements = file_access_ptr->getArray<type>();
    int counter = 0;
    for(const auto& it: listOfElements) {
        //debug statment
        if(it == element) {
            return counter;
        }
        counter++;
    }
    return -1;
}

#endif