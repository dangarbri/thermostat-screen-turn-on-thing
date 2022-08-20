#include <stdio.h>
#include "pico/stdlib.h"
#include "../../src/pwm.h"

/**
 * Testing the PWM module
 */
int main() {
    stdio_init_all();
    sleep_ms(5000);
    puts("Starting up code");

    PWMPin pin{0};
    uint delay_ms = 5000;
    uint16_t ticks = 1300;

    while (true) {
        pin.SetHighTicks(ticks);
        sleep_ms(delay_ms);
        ticks += 25;
    }
}

