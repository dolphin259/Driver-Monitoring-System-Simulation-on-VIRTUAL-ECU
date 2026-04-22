#ifndef DMS_CONTROLLER_H
#define DMS_CONTROLLER_H

#include <systemc.h>

SC_MODULE(DMSController) {
    // 1. Khai báo Cổng (Ports) - Phải có cái này thì file .cpp mới dùng được btn_in
    sc_in<bool> btn_in;
    sc_out<bool> led_out;
    bool led_state;
    void handle_button();
    SC_CTOR(DMSController) : led_state(false) {
        SC_METHOD(handle_button);
        sensitive << btn_in.neg();
    }
};

#endif
