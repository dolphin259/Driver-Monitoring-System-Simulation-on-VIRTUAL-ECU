#ifndef ADC_UNIT_H
#define ADC_UNIT_H

#include <systemc.h>
#include "common.h"
SC_MODULE(ADC_Unit) {
    sc_out<bool> interrupt_signal;
    void process_adc();
    SC_CTOR(ADC_Unit) {
        SC_THREAD(process_adc); 
    }
};

#endif
