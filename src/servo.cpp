#include "servo.h"
#include "pwm.h"

#ifdef DEBUG_SERVO
    #include <stdio.h>
#endif

/**
 * Servo minimum ticks rotate fully clockwise is about 1400 ticks
 * Determined experimentally with an SG92R Micro Servo from Adafruit
 */
#define SERVO_START_TICKS 1400

/**
 * At 8000 ticks the servo is fully counter clockwise
 * Determined experimentally with an SG92R Micro Servo from Adafruit
 */
#define SERVO_END_TICKS 8000

/**
 * Number of ticks to go from start to end
 */
#define SERVO_TICK_DELTA (SERVO_END_TICKS - SERVO_START_TICKS)

/**
 * Number of degrees that make up a half turn
 */
#define HALF_TURN_DEGREES 180

Servo::Servo(uint pin) : _pin (pin) {
}

static uint16_t degrees_to_ticks(uint degrees) {
    // Limit to 180 degrees since my servos only turn 180 degrees
    if (degrees > HALF_TURN_DEGREES) {
        degrees = HALF_TURN_DEGREES;
    }

    float percent = (float) degrees / HALF_TURN_DEGREES;
    uint16_t ticks = (uint16_t) (SERVO_TICK_DELTA * percent);
    return SERVO_START_TICKS + ticks;
}

void Servo::SetRotation(uint degrees) {
#ifdef DEBUG_SERVO
    printf("Setting servo to %d degrees\n", degrees);
#endif
    _pin.SetHighTicks(degrees_to_ticks(degrees));
}

