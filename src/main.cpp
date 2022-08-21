#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "servo.h"
#include "proximity_sensor.h"

void calibrate_servo(Servo& servo) {
    servo.SetRotation(0);
    sleep_ms(1000);
    servo.SetRotation(100);
    sleep_ms(1000);
    servo.SetRotation(0);
    sleep_ms(1000);
}

void turn_on_screen(Servo& servo) {
    // Sometimes you have to whack the screen a few times for it to turn on.
    // More of a physical problem... but we'll solve it with software!
    for (int i = 0; i < 1; i++) {
        servo.SetRotation(100);
        sleep_ms(1000);
        servo.SetRotation(0);
        sleep_ms(1000);
    }
}

int main() {
    bi_decl(bi_program_description("This program will turn on my thermostats when I walk by them."));
    stdio_init_all();

    Servo servo{0};
    calibrate_servo(servo);

    ProximitySensor sensor{2, 3};
    while (1) {
        uint64_t distance = sensor.GetProximity();
        printf("Got proximity reading %llucm\n", distance);
        if (distance < 100) {
            turn_on_screen(servo);
            puts("Sleeping for 30 seconds");
            sleep_ms(30000);
        }
        // Delay so we aren't spamming the proximity sensor too much
    }
}
