#include "../../include/stm32_port/stm32_app.h"
#include "../../include/stm32_port/stm32_bridge.h"
#include <iostream>

extern void App_Init();
extern void App_Run();

namespace GPIO {
    extern GPIOOutput* led;
    extern GPIOEXTI* btn0, *btn1, *btn2, *btn3;
}

void STM32_Application::run_firmware() {
    std::cout << "[Virtual STM32] Thread Firmware đang khởi động" << std::endl;
    App_Init();
    if (GPIO::led)  GPIO::led->sc_port = &led_out;
    if (GPIO::btn0) GPIO::btn0->sc_port = &btn_in;
    if (GPIO::btn1) GPIO::btn1->sc_port = &btn_in;
    if (GPIO::btn2) GPIO::btn2->sc_port = &btn_in;
    if (GPIO::btn3) GPIO::btn3->sc_port = &btn_in;

    App_Run();
}
