#include "../../include/dms_controller.h"
void DMSController::handle_button() {
    if (btn_in.read() == false) {
        std::cout << "@" << sc_time_stamp() << " [DMS]: Đang đổi trạng thái LED" << std::endl;
        led_state = !led_state;
                led_out.write(led_state);
    }
}
