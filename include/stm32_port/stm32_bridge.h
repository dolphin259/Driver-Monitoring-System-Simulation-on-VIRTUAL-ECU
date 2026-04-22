#ifndef STM32_BRIDGE_H
#define STM32_BRIDGE_H

#include <systemc.h>
#include <iostream>
namespace GPIO {
    enum class PinState { LOW = 0, HIGH = 1 };
    class GPIOOutput {
    public:
        sc_out<bool>* sc_port;
        GPIOOutput(void* port, int pin, ...) : sc_port(nullptr) {}
        void set() { if(sc_port) sc_port->write(true); }
        void reset() { if(sc_port) sc_port->write(false); }
        void toggle() { if(sc_port) sc_port->write(!sc_port->read()); }
    };
    class GPIOEXTI {
    public:
        sc_in<bool>* sc_port;
        GPIOEXTI(void* port, int pin, ...) : sc_port(nullptr) {}
        
        void enableInterrupt() {}
        bool isInterruptEnabled() { return true; }
        PinState read() {
            return (sc_port && sc_port->read()) ? PinState::HIGH : PinState::LOW;
        }
        void setCallback(void (*cb)()) {} // Tạm thời để trống
    };
}
#define GPIOB (void*)0x40020400
#define GPIOC (void*)0x40020800
#define __NOP()
#endif
