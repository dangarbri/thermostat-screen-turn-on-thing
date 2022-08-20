#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "servo.h";
#include "proximity_sensor.h";

int main() {
    bi_decl(bi_program_description("This program will turn on my thermostats when I walk by them."));
    stdio_init_all();

    Servo servo{22};
    ProximitySensor sensor{0, 1};
    while (1) {
        puts("Starting main loop");
        puts("Getting sensor reading");
        uint64_t distance = sensor.GetProximity();
        printf("Got proximity reading %llucm\n", distance);
        if (distance < 100) {
            puts("Enabling servo");
            // Turn servo
            servo.on();
            // Delay 10 seconds
            puts("Waiting 10 seconds");
            sleep_ms(10000);
            servo.off();
        }
    }
}
