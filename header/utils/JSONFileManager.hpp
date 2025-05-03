#ifndef _JSON_FILE_MANAGER_HPP
#define _JSON_FILE_MANAGER_HPP
#include "FileManager.hpp"
#include <string>
#include <deque>
#include "../nlohmann/json.hpp"
#include "../nlohmann/adl_serializer_admin.hpp"
#include "../nlohmann/adl_serializer_aircraft.hpp"
#include "../nlohmann/adl_serializer_bookingAgent.hpp"
#include "../nlohmann/adl_serializer_flight.hpp"
#include "../nlohmann/adl_serializer_passenger.hpp"

using File_mPtr = std::shared_ptr<FileManager>;
using json = nlohmann::json;
class JSONFileManager {
    private:
    File_mPtr file_mPtr;
    json jsonArray;
    public:
    JSONFileManager(std::string path);
    JSONFileManager() = delete;
    JSONFileManager(const JSONFileManager &other) = default;
    JSONFileManager(JSONFileManager && other) = default;
    bool append(json jsonObj, int index = -1);
    template<typename type> type read(int index);
    bool erase(int index);
    int getFileSize();
    File_ptr getFstream();
};
#endif // !1

template <typename type>
inline type JSONFileManager::read(int index)
{
    if(index < jsonArray.size()) {
        return jsonArray.at(index).get<type>();
    }
    return type();
}
