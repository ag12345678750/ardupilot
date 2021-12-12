/*
   This program is an extension of the ardupilot project supports
   additional sources of location data. 
   The base line of this program is to get location data from an 
   additional hardware/software module, to create by help of Kalmap 
   filter approximated trajectory,send new location back to device
    and to support existing GPS in a case of some problems.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
   Created on: 9 Dec 2021
       Author: Alex
*/
 
#pragma once

#include <inttypes.h>
#include <AP_Common/AP_Common.h>
#include <AP_Param/AP_Param.h>>
#include <AP_GPS>
/*
   maximum number of GPS instances available on this platform. If more
   than 1 then redundant sensors may be available
*/
// #define GPS_MAX_INSTANCES  (GPS_MAX_RECEIVERS + 1) // maximum number of GPs instances including the 'virtual' GPS created by blending receiver data

// the number of GPS leap seconds
// #define GPS_LEAPSECONDS_MILLIS 18000ULL

// #define UNIX_OFFSET_MSEC (17000ULL * 86400ULL + 52ULL * 10ULL * AP_MSEC_PER_WEEK - GPS_LEAPSECONDS_MILLIS)

/// @class AP_GPS
/// GPS driver main class
class AP_PS_GPS:AP_GPS
{
public:

    // constructor
    AP_PS_GPS();

    // GPS driver types - get it from the AP_GPS class
    /*
    enum GPS_Type {
        GPS_TYPE_NONE  = 0,
        GPS_TYPE_AUTO  = 1,
        GPS_TYPE_UBLOX = 2,
        GPS_TYPE_MTK   = 3,
        GPS_TYPE_MTK19 = 4,
        GPS_TYPE_NMEA  = 5,
        GPS_TYPE_SIRF  = 6,
        GPS_TYPE_HIL   = 7,
        GPS_TYPE_SBP   = 8,
        GPS_TYPE_UAVCAN = 9,
        GPS_TYPE_SBF   = 10,
        GPS_TYPE_GSOF  = 11,
        GPS_TYPE_QURT  = 12,
        GPS_TYPE_ERB = 13,
        GPS_TYPE_MAV = 14,
        GPS_TYPE_NOVA = 15
    };
    */

    /// GPS status codes
    /*
    enum GPS_Status {
        NO_GPS = GPS_FIX_TYPE_NO_GPS,                     ///< No GPS connected/detected
        NO_FIX = GPS_FIX_TYPE_NO_FIX,                     ///< Receiving valid GPS messages but no lock
        GPS_OK_FIX_2D = GPS_FIX_TYPE_2D_FIX,              ///< Receiving valid messages and 2D lock
        GPS_OK_FIX_3D = GPS_FIX_TYPE_3D_FIX,              ///< Receiving valid messages and 3D lock
        GPS_OK_FIX_3D_DGPS = GPS_FIX_TYPE_DGPS,           ///< Receiving valid messages and 3D lock with differential improvements
        GPS_OK_FIX_3D_RTK_FLOAT = GPS_FIX_TYPE_RTK_FLOAT, ///< Receiving valid messages and 3D RTK Float
        GPS_OK_FIX_3D_RTK_FIXED = GPS_FIX_TYPE_RTK_FIXED, ///< Receiving valid messages and 3D RTK Fixed
    };
    */
    
    /*
    enum GPS_Config {
        GPS_ALL_CONFIGURED = 255
    };
    */

    /*
      The GPS_State structure is filled in by the backend driver as it
      parses each message from the GPS.
    */

    struct GPS_State {
        uint8_t instance; // the instance number of this GPS

        // all the following fields must all be filled by the backend driver
        GPS_Status status;                  ///< driver fix status
        uint32_t time_week_ms;              ///< GPS time (milliseconds from start of GPS week)
        uint16_t time_week;                 ///< GPS week number
        Location location;                  ///< last fix location
        float ground_speed;                 ///< ground speed in m/sec
        float ground_course;                ///< ground course in degrees
        uint16_t hdop;                      ///< horizontal dilution of precision in cm
        uint16_t vdop;                      ///< vertical dilution of precision in cm
        uint8_t num_sats;                   ///< Number of visible satellites
        Vector3f velocity;                  ///< 3D velocity in m/s, in NED format
        float speed_accuracy;               ///< 3D velocity RMS accuracy estimate in m/s
        float horizontal_accuracy;          ///< horizontal RMS accuracy estimate in m
        float vertical_accuracy;            ///< vertical RMS accuracy estimate in m
        bool have_vertical_velocity:1;      ///< does GPS give vertical velocity? Set to true only once available.
        bool have_speed_accuracy:1;         ///< does GPS give speed accuracy? Set to true only once available.
        bool have_horizontal_accuracy:1;    ///< does GPS give horizontal position accuracy? Set to true only once available.
        bool have_vertical_accuracy:1;      ///< does GPS give vertical position accuracy? Set to true only once available.
        uint32_t last_gps_time_ms;          ///< the system time we got the last GPS timestamp, milliseconds

        // all the following fields must only all be filled by RTK capable backend drivers
        uint32_t rtk_age_ms;               ///< GPS age of last baseline correction in milliseconds  (0 when no corrections, 0xFFFFFFFF indicates overflow)
        uint8_t  rtk_num_sats;             ///< Current number of satellites used for RTK calculation
    };
    
    
    // 
    // Next lines are new procedures for new device support
    //
    bool apply_new_point(const char* input_str);
    GPS_State* parse_PS_massage(const char* new_msg);
    bool send_new_location_ack(GPS_State new_point);
    
 };
