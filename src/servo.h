#include "pwm.h"

/**
 * Basic servo driver. Drives a servo by using the
 * built-in PWM controller to send a pulse every
 * 50Hz.
 *
 * This implementation is based on the servo description
 * of this wikipedia article: https://en.wikipedia.org/wiki/Servo_control
 * Key points:
 *   - Uses a clock divider to get the PWM counter to wrap 50 times a second (50Hz)
 *   - PWM counter is 65535.
 *   - Experimentally I found 1400 ticks to be 0 turn and 8000 to be 100% (180degree) turn on the servo
 *   - If these tick values don't work for you'll have to experiment on your own.
 *
 */
class Servo {
public:
    /**
     * Initializes the servo on the given control pin
     * @param[in] pin Servo control pin
     */
    Servo(uint pin);

    /**
     * Sets the rotation of the servo in terms of % turned
     * Limited to 180 degrees. If you specify a value greater than 180
     * then this will only turn to 180 degrees
     * @param[in] percentage Percentage to rotate the servo
     */
    void SetRotation(uint degrees);

private:
    /**
     * Current pin selected for this servo
     */
    PWMPin _pin;
};

