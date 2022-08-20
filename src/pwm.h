#pragma once

#include "pico/stdlib.h"

/**
 * PWM interface.
 * Currently only runs with a PWM frequency of 50Hz
 * TODO: Add calculations to set frequency dynamically
 */
class PWMPin {
public:
    /**
     * Initializes PWM on a pin to the given frequency and enables it.
     * @note In the PWM hardware, each slice is tied to two pins
     *       and they must share a clock frequency. Make sure
     *       to account for this in your design
     *
     * @param[in] pin GPIO pin number
     */
    PWMPin(uint pin);

    /**
     * Free's impl pointer
     * @private
     */
    ~PWMPin();

    /**
     * Sets the duty cycle to the given percentage
     * Cycle will be high for the given percentage
     * @param[in] percentage % of time to stay high
     */
    void SetDutyCycle(float percentage);

    /**
     * Sets the number of ticks for PWM to stay high
     * The PWM counter wraps at uint16_t max (65535)
     * @note May be used instead of SetDutyCycle.
     * @param[in] ticks Number of ticks to stay high
     */
    void SetHighTicks(uint16_t ticks);

    /**
     * Enable PWM hardware
     */
    void Enable();

    /**
     * Disable PWM hardware
     */
    void Disable();
private:
    struct impl;
    impl* _impl;
};
