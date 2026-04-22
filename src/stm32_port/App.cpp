#include "../../include/stm32_port/stm32_bridge.h"
#include "../../include/common.h"
#include <cstdio>
#include <thread>

extern Register*** ECU_Memory;
namespace GPIO {
    GPIOOutput* led = nullptr;
    GPIOEXTI* btn0 = nullptr, *btn1 = nullptr, *btn2 = nullptr, *btn3 = nullptr;
}
using namespace GPIO;
static uint32_t ledPattern = 0;

void App_Init(void) {
    printf("Khởi chạy firmware STM32 \n");
    led = new GPIOOutput(GPIOB, 11);
    btn3 = new GPIOEXTI(GPIOC, 3);
    ledPattern = 0;
}

void App_Run(void) {
    uint32_t counter = 0;
    int last_temp = -1;
    static int lastPattern = -1;
    static bool isWarningMuted = false;
    while (true) {
        if (ECU_Memory && ECU_Memory[0][0]) {
            int current_temp = *ECU_Memory[0][0];
            
            bool isNewDataFromPipe = (ECU_Memory[0][2] && *ECU_Memory[0][2] == 1);

            if (isNewDataFromPipe) {
                isWarningMuted = false;
                *ECU_Memory[0][2] = 0;
                if (current_temp != last_temp) {
                    printf("[STM32] @%s -> Cập nhật nhiệt độ: %d°C\n",
                            sc_time_stamp().to_string().c_str(), current_temp);
                    last_temp = current_temp;
                }
            }
            if (current_temp > 800 && !isWarningMuted) {
                if (ledPattern != 3) {
                    ledPattern = 3;
                    printf("[STM32]CẢNH BÁO: QUÁ NHIỆT (%d°C)\n", current_temp);
                }
            }
            else if (current_temp <= 800 && current_temp > 0 && ledPattern == 3) {
                ledPattern = 0;
                isWarningMuted = false;
                printf("[STM32] -> Hệ thống đã mát (%d°C). Tắt cảnh báo.\n", current_temp);
            }
        }
        if (ECU_Memory && ECU_Memory[0][1]) {
            int cmd = *ECU_Memory[0][1];
            if (cmd >= 0 && cmd <= 3) {
                int temp = (ECU_Memory[0][0]) ? *ECU_Memory[0][0] : 0;
                if (cmd == 0 && temp > 800) {
                    isWarningMuted = true;
                    printf("[STM32] Mailbox: Xác nhận lỗi. Tạm dừng nháy đèn.\n");
                } else {
                    printf("[STM32] Mailbox: Chuyển sang Pattern %d\n", cmd);
                }

                ledPattern = (uint32_t)cmd;
                *ECU_Memory[0][1] = -1;
                counter = 0;
            }
        }
        if (ledPattern != lastPattern) {
            switch (ledPattern) {
                case 0: printf("[STM32] Status: LED đã TẮT.\n"); break;
                case 1: printf("[STM32] Status: LED đã SÁNG ĐỨNG IM.\n"); break;
                case 2: printf("[STM32] Status: Chế độ NHÁY CHẬM.\n"); break;
                case 3: printf("[STM32] Status: Chế độ BÁO ĐỘNG NHÁY NHANH.\n"); break;
            }
            lastPattern = ledPattern;
        }
        switch (ledPattern) {
            case 0: led->reset(); break;
            case 1: led->set(); break;
            case 2: // Nháy chậm (1s)
                if (++counter >= 5) {
                    led->toggle();
                    printf("[STM32] @%s -> LED nháy chậm\n", sc_time_stamp().to_string().c_str());
                    counter = 0;
                }
                break;
            case 3: 
                if (++counter >= 1) {
                    led->toggle();
                    printf("[STM32] @%s -> !!! ĐANG NHÁY CẢNH BÁO !!!\n", sc_time_stamp().to_string().c_str());
                    counter = 0;
                }
                break;
        }

        wait(200, SC_MS);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
