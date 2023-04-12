#include <bsp/board.h>
#include <tusb.h>

#include "pico/time.h"

bool device_connected = false;
uint8_t dev_addr;
uint8_t instance;

int main() {
    board_init();
    tusb_init();

    uint64_t prev_toggle = 0;
    uint8_t state = 0;

    while (true) {
        tuh_task();

        uint64_t now = time_us_64();

        if (device_connected && (now - prev_toggle > 100000)) {
            state = !state;
            prev_toggle = now;
            board_led_write(tuh_hid_set_report(dev_addr, instance, 99, HID_REPORT_TYPE_OUTPUT, &state, 1));
        }
    }

    return 0;
}

void tuh_hid_mount_cb(uint8_t dev_addr_, uint8_t instance_, uint8_t const* desc_report, uint16_t desc_len) {
    dev_addr = dev_addr_;
    instance = instance_;
    device_connected = true;
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
    device_connected = false;
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
}
