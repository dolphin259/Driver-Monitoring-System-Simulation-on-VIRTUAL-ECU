#ifndef STM32_APP_H
#define STM32_APP_H

#include <systemc.h>
#include "stm32_bridge.h"
SC_MODULE(STM32_Application) {
    sc_in<bool> btn_in;
    sc_out<bool> led_out;

    SC_CTOR(STM32_Application) {
        SC_THREAD(run_firmware);
    }

    void run_firmware();
};

#endif
