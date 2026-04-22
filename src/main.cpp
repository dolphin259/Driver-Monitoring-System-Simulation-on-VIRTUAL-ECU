#include <systemc.h>
#include "../include/common.h"
#include "../include/adc_unit.h"
#include "../include/stm32_port/stm32_app.h"
#include "../include/dms_controller.h"
Register*** ECU_Memory = nullptr;

void init_system_memory() {
    if (ECU_Memory != nullptr) return;
    ECU_Memory = new Register**[1];
    ECU_Memory[0] = new Register*[3];
    ECU_Memory[0][0] = new Register(0);
    ECU_Memory[0][1] = new Register(-1); 
    ECU_Memory[0][2] = new Register(0);
    std::cout << "[System] Đã khởi tạo vùng nhớ MMIO.\n";
}

int sc_main(int argc, char* argv[]) {
    init_system_memory();
    sc_signal<bool> irq_line;
    sc_signal<bool> sig_led;
    sc_signal<bool> dms_warning;
    ADC_Unit adc("Virtual_ADC_Unit");
    adc.interrupt_signal(irq_line);

    STM32_Application stm32_firmware("STM32_Logic");
    stm32_firmware.btn_in(irq_line);
    stm32_firmware.led_out(sig_led);

    DMSController dms("DMS_Module");
    dms.btn_in(irq_line);
    dms.led_out(dms_warning);
    std::cout << "HỆ THỐNG VIRTUAL ECU KHỞI ĐỘNG \n";
    sc_start(); // Chạy vô hạn
    return 0;
}
