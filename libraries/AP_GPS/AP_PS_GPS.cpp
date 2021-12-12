/*
   This program is an extension of the ardupilot project supports
   additional sources of location data.
   The base line of this program is to get location data from an
   additional hardware/software module, to create by help of Kalmap
   filter approximated trajectory and to support existing GPS
   in a case of some problems.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Created on: 9 Dec 2021
       Author: Alex
 */

// Check if we need all these files
#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>
#include <AP_Notify/AP_Notify.h>
#include <GCS_MAVLink/GCS.h>
#include <AP_BoardConfig/AP_BoardConfig.h>
#include <climits>

#include "AP_GPS_NOVA.h"
#include "AP_GPS_ERB.h"
#include "AP_GPS_GSOF.h"
#include "AP_GPS_MTK.h"
#include "AP_GPS_MTK19.h"
#include "AP_GPS_NMEA.h"
#include "AP_GPS_QURT.h"
#include "AP_GPS_SBF.h"
#include "AP_GPS_SBP.h"
#include "AP_GPS_SBP2.h"
#include "AP_GPS_SIRF.h"
#include "AP_GPS_UBLOX.h"
#include "AP_GPS_MAV.h"
#include "GPS_Backend.h"


// #include "rapidjson/document.h"
// #include "rapidjson/writer.h"
// #include "rapidjson/stringbuffer.h"
// #include "AP_GPS.h"
#include "AP_PS_GPS.h"
#include <iostream>
#include <cmath>
#include <nlohmann/json.hpp>

#include <iomanip>

using namespace std;
using json = nlohmann::json;


#define GPS_BAUD_TIME_MS 1200

// constructor
AP_PS_GPS::AP_PS_GPS()
{
    static_assert((sizeof(_initialisation_blob) * (CHAR_BIT + 2)) < (4800 * GPS_BAUD_TIME_MS * 1e-3),
                    "GPS initilisation blob is to large to be completely sent before the baud rate changes");

    AP_Param::setup_object_defaults(this, var_info);
}

bool AP_PS_GPS::apply_new_point(const char* input_str)
{

    GPS_State* new_loc;
    new_loc = parse_PS_massage(input_str);

    return true;
}

AP_PS_GPS::GPS_State* AP_PS_GPS::parse_PS_massage(const char* input_str)
{
    GPS_State* new_loc = new GPS_State;
    json myDoc1;

    // location : lat,long,alt
    // timestamp
    // ???


    // json::Reader reader;
    // json::Value cfg_root;

    // Parse the JSON string into DOM
    // Document mydoc;
    // mydoc.Parse(input_str);  // or parse

    // auto new_obj = json::Parse(string(input_str));  // or parse
    auto new_obj = json::parse(input_str);  // or parse


    return new_loc;
}

bool AP_PS_GPS::send_new_location_ack(GPS_State new_point)
{
    return true;
}
