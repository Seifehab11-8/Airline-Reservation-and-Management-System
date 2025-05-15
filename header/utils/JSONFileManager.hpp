#ifndef _JSON_FILE_MANAGER_HPP
#define _JSON_FILE_MANAGER_HPP
#include "FileManager.hpp"
#include <string>
#include <vector>
#include "../nlohmann/json.hpp"
#include "../nlohmann/adl_serializer_admin.hpp"
#include "../nlohmann/adl_serializer_aircraft.hpp"
#include "../nlohmann/adl_serializer_bookingAgent.hpp"
#include "../nlohmann/adl_serializer_flight.hpp"
#include "../nlohmann/adl_serializer_crewAttendant.hpp"
#include "../nlohmann/adl_serializer_passenger.hpp"
#include "../nlohmann/adl_serializer_reservation.hpp"

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
    template<typename type> std::vector<type> getArray();
    bool erase(int index);
    template <typename type> bool update(int index, const type& new_version);
    int getFileSize();
    File_ptr getFstream();
};


using Json_file_ptr = std::shared_ptr<JSONFileManager>;
template <typename type>
inline type JSONFileManager::read(int index)
{
    if(index < jsonArray.size()) {
        return jsonArray.at(index).get<type>();
    }
    return type();
}

template <typename type>
inline std::vector<type> JSONFileManager::getArray()
{
    std::vector<type> result;
    for (const auto& item : jsonArray) {
        result.push_back(item.get<type>());
    }
    return result;
}

template <typename type>
inline bool JSONFileManager::update(int index, const type &new_version)
{
    if(index < static_cast<int>(jsonArray.size()) && index >= 0) { // Fix signed/unsigned mismatch
        jsonArray.at(index) = json(new_version);     // Serialize new_version to JSON
        file_mPtr->append(jsonArray.dump(4),0, true);
        return true;
    }
    return false;
}

#endif // !1