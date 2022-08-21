#include "proximity_sensor.h"
#include "pico/stdlib.h"
#ifdef DEBUG_PROXIMITY_SENSOR
    #include <stdio.h>
#endif

#define SAMPLE_DURATION_60_MS 60

/**
 * Documentation states set trigger high for at least 10us
 */
#define TRIGGER_HIGH_TIME_US 10

ProximitySensor::ProximitySensor(uint trigger_pin, uint echo_pin) {
    _trigger = trigger_pin;
    gpio_init(_trigger);
    gpio_set_dir(_trigger, GPIO_OUT);
#ifdef DEBUG_PROXIMITY_SENSOR
    printf("Set sensor trigger pin to %d\n", trigger_pin);
#endif

    _echo = echo_pin;
    gpio_init(_echo);
    gpio_set_dir(_echo, GPIO_IN);
#ifdef DEBUG_PROXIMITY_SENSOR
    printf("Set sensor echo pin to %d\n", echo_pin);
#endif
}

uint64_t ProximitySensor::GetProximity() {
    // Initialize sample variables for number of samples and cumulative
    // readings
    uint64_t sample_count = 0;
    uint64_t sample_total = 0;
    do {
        sample_total += GetSample();
        sample_count += 1;
        // For sanity, let the pins stay low for a time after
        // reading the sample
        sleep_us(10);
        // for a reading, each cm is 58us, so 1000 * 58 = 58000us or 58ms.
        // Product sheet recommends sampling for at least 60ms.
        // Code managing this loop based on the clock tended to
        // hang, so using measurement to cap it instead.
    } while (sample_total < 1000);
    return sample_total / sample_count;
}

uint64_t ProximitySensor::GetSample() {
#ifdef DEBUG_PROXIMITY_SENSOR
    puts("Polling proximity");
#endif
    // Send trigger signal
    _SendTrigger();
    // Wait for echo signal
    _WaitForEchoToBe(true);
    uint duration = _GetEchoHighDuration();
#ifdef DEBUG_PROXIMITY_SENSOR
    printf("Got echo signal for %dus\n", duration);
#endif
    return _CalculateDistance(duration);
}

void ProximitySensor::_SendTrigger() {
    gpio_put(_trigger, true);
    sleep_us(TRIGGER_HIGH_TIME_US);
    gpio_put(_trigger, false);
}

void ProximitySensor::_WaitForEchoToBe(bool target) {
    // Wait for echo signal to go high
    bool echo;
#ifdef DEBUG_PROXIMITY_SENSOR
    // For debug, track number of reads echo is high
    uint count = 0;
#endif
    do {
        echo = gpio_get(_echo);
#ifdef DEBUG_PROXIMITY_SENSOR
        count++;
#endif
    } while (echo != target);
#ifdef DEBUG_PROXIMITY_SENSOR
    printf("Echo was %d for %d reads\n", !target, count);
#endif
}

uint64_t ProximitySensor::_GetEchoHighDuration() {
    absolute_time_t start = get_absolute_time();
    _WaitForEchoToBe(false);
    absolute_time_t end = get_absolute_time();

    uint64_t start_us = to_us_since_boot(start);
    uint64_t end_us = to_us_since_boot(end);
#ifdef DEBUG_PROXIMITY_SENSOR
    printf("Start timestamp: %llu\n", start_us);
    printf("End timestamp: %llu\n", end_us);
#endif
    return end_us - start_us;
}

uint64_t ProximitySensor::_CalculateDistance(uint64_t duration_us) {
    // Formula for centimeters is uS / 58
    return duration_us / 58;
}


