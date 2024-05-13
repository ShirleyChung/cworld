#ifndef _map_of_earth_for_person_to_travel_and_leave_items_2024_
#define _map_of_earth_for_person_to_travel_and_leave_items_2024_

#include "object.h"

// 人事物所在地點
struct Location {
    int x_;
    int y_;
    std::string desc_;
};

// 管理物件所在位置
class LocationManager {
    static std::vector<Location*> location_list_;
public:
    LocationManager() {}
};

#endif
