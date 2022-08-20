#include "proximity_sensor.h"
#include <stdio.h>
#include "pico/stdlib.h"

/**
 * Documentation states set trigger high for at least 10us
 */
#define TRIGGER_HIGH_TIME_US 10

ProximitySensor::ProximitySensor(uint trigger_pin, uint echo_pin) {
    _trigger = trigger_pin;
    gpio_init(_trigger);
    gpio_set_dir(_trigger, GPIO_OUT);

    _echo = echo_pin;
    gpio_init(_echo);
    gpio_set_dir(_echo, GPIO_IN);
}

uint64_t ProximitySensor::GetProximity() {
    puts("Polling proximity");
    // Send trigger signal
    _SendTrigger();
    // Wait for echo signal
    _WaitForEcho();
    uint duration = _GetEchoHighDuration();
    return _CalculateDistance(duration);
}

void ProximitySensor::_SendTrigger() {
    gpio_put(_trigger, 1);
    sleep_us(TRIGGER_HIGH_TIME_US);
    gpio_put(_trigger, 0);
}

void ProximitySensor::_WaitForEcho() {
    // Wait for echo signal to go high
    while (gpio_get(_echo) == false) {}
}

uint64_t ProximitySensor::_GetEchoHighDuration() {
    absolute_time_t start = get_absolute_time();
    while (gpio_get(_echo) == true) {}
    absolute_time_t end = get_absolute_time();

    uint64_t start_us = to_us_since_boot(start);
    uint64_t end_us = to_us_since_boot(start);
    return end_us - start_us;
}

uint64_t ProximitySensor::_CalculateDistance(uint64_t duration_us) {
    // Formula for centimeters is uS / 58
    return duration_us / 58;
}


