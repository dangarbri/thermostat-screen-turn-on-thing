#include <stdio.h>
#include "pico/stdlib.h"
#include "servo.h"

/**
 * This test will control the servo to go 0%, 50%, and 100% rotation
 * in a loop
 */
int main() {
    stdio_init_all();
    // Initial delay so I can connect before code executes
    sleep_ms(5000);

    Servo servo{0};
    uint delay_ms = 3000;
    uint degrees = 0;
    while (true) {
        servo.SetRotation(degrees);
        sleep_ms(delay_ms);
        degrees += 180;
        if (degrees > 180) {
            degrees = 0;
        }
    }
}

