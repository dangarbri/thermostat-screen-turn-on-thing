#include "proximity_sensor.h"
#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    sleep_ms(5000);

    uint delay_ms = 1000;

    puts("Initializing proximity sensor");
    ProximitySensor sensor{2, 3};

    while (true) {
        /*
        absolute_time_t start = get_absolute_time();
        auto res = to_us_since_boot(start);
        printf("Current time in us: %llu\n", res);
        */
        uint64_t reading = sensor.GetProximity();
        printf("Get sensor reading of %llu\n", reading);
        sleep_ms(delay_ms);
    }
}

