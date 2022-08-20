#include "hardware/gpio.h"

/**
 * Basic servo driver.
 * Does not support PWM
 */
class Servo {
public:
    /**
     * Initializes the servo on the given control pin
     * @param[in] pin Servo control pin
     */
    Servo(uint pin);

    /**
     * Enables the servo, turns it on 100%
     */
    void on();

    /**
     * Disables the servo. Twist back to normal.
     */
    void off();

private:
    /**
     * Current pin selected for this servo
     */
    uint _pin;
};

