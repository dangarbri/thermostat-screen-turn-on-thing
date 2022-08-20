#include "pwm.h"

/**
 * Basic servo driver. Drives a servo by using the
 * built-in PWM controller to send a pulse every
 * 50Hz.
 *
 * This implementation is based on the servo description
 * of this wikipedia article: https://en.wikipedia.org/wiki/Servo_control
 * Key points:
 *   - Uses a clock frequency of 50Hz
 *   - 90 degree turn = 1.5ms pulse / 20ms (50Hz) = 7.5% duty cycle
 *   - Assumption: Doubling the pulse will double the rotation
 *     * 180 degree turn = 3ms pulse / 20ms (50Hz) = 15% duty cycle
 *
 * If your servo doesn't respond to the above, then you
 * need to find and check your datasheet to figure out
 * what frequency it needs to run at
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

