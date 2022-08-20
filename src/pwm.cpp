#include "pwm.h"
#include "hardware/pwm.h"

// Include stdio for printf if debug is enabled
#ifdef DEBUG_PWM
    #include <stdio.h>
#endif

/**
 * @private
 */
struct PWMPin::impl {
    /**
     * Sets the pin to use PWM, builds up some state for managing the
     * frequency, and enables PWM
     */
    void InitPWM(uint pin);

    /**
     * Pin being controlled
     */
    uint pin;

    /**
     * PWM slice for the pin
     */
    uint slice;

    /**
     * Sets the PWM frequency to 50Hz
     */
    void SetFrequencyTo50Hz();

    /**
     * Enable PWM HW to start pulsing
     */
    void EnablePWM();

    /**
     * Stop PWM HW
     */
    void DisablePWM();

    /**
     * Sets the duty cycle to the given percentage
     * @param[in] percentage Value to set the duty cycle to.
     */
    void SetDutyCycle(float percentage);

    /**
     * Sets PWM channel to the given number of ticks
     * @param[in] ticks Number of ticks to be high
     */
    void SetHighTicks(uint16_t ticks);
};



void PWMPin::impl::InitPWM(uint pin) {
    // Set the pin to use the PWM hardware
    gpio_set_function(pin, GPIO_FUNC_PWM);
    // Sets the pin's frequency to the given frequency
    SetFrequencyTo50Hz();
    // Enable PWM
    EnablePWM();
}

void PWMPin::impl::EnablePWM() {
    pwm_set_enabled(slice, true);
}

void PWMPin::impl::DisablePWM() {
    pwm_set_enabled(slice, false);
}

void PWMPin::impl::SetFrequencyTo50Hz() {
    // White board math that I barely understand indicates that
    // with the pico's default 125MHz frequency, we can divide it
    // by 38.1476 to get our PWM frequency to 50Hz
    pwm_set_clkdiv(slice, 38.1476);
#ifdef DEBUG_PWM
    puts("Set clock divider to 38.1476 for 50Hz PWM frequency");
#endif
}

void PWMPin::impl::SetDutyCycle(float percentage) {
    float ticks_f = percentage / 100.0f * 65535;
    uint16_t ticks = static_cast<uint16_t>(ticks_f);
    SetHighTicks(ticks);
}

void PWMPin::impl::SetHighTicks(uint16_t ticks) {
#ifdef DEBUG_PWM
    printf("Setting PWM counter to %d ticks\n", ticks);
#endif
    pwm_set_gpio_level(pin, ticks);
    // Reset PWM counter
    // TODO: Not sure if this is appropriate
    // pwm_set_counter(slice, 0);
}

PWMPin::PWMPin(uint pin) {
    _impl = new impl();
    _impl->pin = pin;
    _impl->slice = pwm_gpio_to_slice_num(pin);
    _impl->InitPWM(pin);
}

void PWMPin::Enable() {
    _impl->EnablePWM();
}

void PWMPin::Disable() {
    _impl->DisablePWM();
}

void PWMPin::SetDutyCycle(float percentage) {
    _impl->SetDutyCycle(percentage);
}

void PWMPin::SetHighTicks(uint16_t ticks) {
    _impl->SetHighTicks(ticks);
}


PWMPin::~PWMPin() { delete _impl; };
