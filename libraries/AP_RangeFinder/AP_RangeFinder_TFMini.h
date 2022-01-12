#pragma once

#include "RangeFinder.h"
#include "RangeFinder_Backend.h"

class AP_RangeFinder_TFMini: public AP_RangeFinder_Backend
{

public:

    enum benewake_model_type {
        BENEWAKE_TF02 = 0,
        BENEWAKE_TFmini = 1,
        BENEWAKE_TF03 = 2,
    };
    
    // constructor
    AP_RangeFinder_TFMini(RangeFinder &ranger, 
            uint8_t instance, 
            RangeFinder::RangeFinder_State &_state,
            MAV_DISTANCE_SENSOR model);

    // static detection function
    static bool detect(RangeFinder &ranger, uint8_t instance);

    // update state
    void update(void) override;

private:   // Temporary
    // get a reading
    // distance returned in reading_cm
    bool get_reading(uint16_t &reading_cm);

    AP_HAL::UARTDriver *uart = nullptr;
    MAV_DISTANCE_SENSOR s_model_type;
    benewake_model_type model_type;
    uint32_t last_reading_ms = 0;
    char linebuf[10];
    uint8_t linebuf_len = 0;
};
