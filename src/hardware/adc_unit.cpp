#include "../../include/adc_unit.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

void ADC_Unit::process_adc() {
    int last_val = -1;
        int fd = open("sensor_pipe", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        std::cerr << "[Hardware] LỖI: Không thể mở sensor_pipe" << std::endl;
    }

    while (true) {
        if (fd != -1) {
            char buffer[16] = {0};
            ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
            
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                int val = atoi(buffer);
                if (val >= 0 && val <= 3) {
                    if (val != last_val) {
                        if (ECU_Memory && ECU_Memory[0][1]) *ECU_Memory[0][1] = val;
                        interrupt_signal.write(true);
                        wait(10, SC_MS);
                        interrupt_signal.write(false);
                        
                        last_val = val;
                    }
                }
                else {
                    if (ECU_Memory && ECU_Memory[0][0]) {
                        *ECU_Memory[0][0] = val; // Cập nhật giá trị MMIO
                        
                        // RUNG CHUÔNG: Bật cờ [0][2] báo cho Firmware biết có dữ liệu mới đổ vào
                        if (ECU_Memory[0][2]) *ECU_Memory[0][2] = 1;
                    }
                    interrupt_signal.write(val > 800);
                    
                    last_val = val;
                }
            }
        }
        
        wait(100, SC_MS);
    }
    }
