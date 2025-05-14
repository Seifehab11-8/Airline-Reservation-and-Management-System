#pragma once
#include "json.hpp"
#include "../flight/Aircraft.hpp"

namespace nlohmann 
{
    template<>
    struct adl_serializer<Aircraft>
    {
        static void to_json(json &j, const Aircraft &aircraft)
        {
            j = json {
                {"ID", aircraft.getID()},
                {"model", aircraft.getModel()},
                {"manufacturer", aircraft.getManufacturer()},
                {"seating capacity", aircraft.getSeatingCapacity()},
                {"range", aircraft.getRange()},
                {"maintenance history", aircraft.getMaintenanceHistory()},
                {"last maintenance date", (*(aircraft.getLastMaintenanceDate())).to_string()},
                {"next maintenance date", (*(aircraft.getNextMaintenanceDate())).to_string()}
            };
        }
        static void from_json(const json &j, Aircraft &aircraft)
        {
            aircraft.setID(j.value("ID", ""));
            aircraft.setModel(j.value("model", ""));
            aircraft.setManufacturer(j.value("manufacturer", ""));
            aircraft.setSeatingCapacity(j.value("seating capacity", 0));
            aircraft.setRange(j.value("range", 0.0));
            aircraft.setMaintenanceHistory(j.value("maintenance history", std::vector<std::string>()));
            
            auto last_maintenance_str = j.value("last maintenance date", "");
            if (!last_maintenance_str.empty()) {
                auto last_maintenance_ptr = std::make_shared<Date>();
                last_maintenance_ptr->from_string(last_maintenance_str);
                aircraft.setLastMaintenanceDate(last_maintenance_ptr);
            }
            
            auto next_maintenance_str = j.value("next maintenance date", "");
            if (!next_maintenance_str.empty()) {
                auto next_maintenance_ptr = std::make_shared<Date>();
                next_maintenance_ptr->from_string(next_maintenance_str);
                aircraft.setNextMaintenanceDate(next_maintenance_ptr);
            }
        }
    };
} // namespace nlohmann