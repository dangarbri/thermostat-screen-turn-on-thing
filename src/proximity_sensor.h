#include "hardware/gpio.h"

/**
 * Drives a basic proximity sensor
 */
class ProximitySensor {
public:
    /**
     * Initializes a proximity sensor with the given trigger
     * and echo gpio pins
     * @param[in] trigger_pin The pin wired to the trigger signal
     * @param[in] echo_pin The pin wired to the echo signal
     */
    ProximitySensor(uint trigger_pin, uint echo_pin);

    /**
     * Blocking call that will get a reading from the sensor
     * @returns calculated distance in (TODO: what unit is this?
     */
    uint64_t GetProximity();
private:
    /**
     * Trigger pin number
     */
    uint _trigger;

    /**
     * Echo pin number
     */
    uint _echo;

    /**
     * Sends the trigger signal to get a reading
     */
    void _SendTrigger();

    /**
     * Wait for echo pin to reach the given state
     * @param[in] high Set to true to wait for pin to go high, false for low
     */
    void _WaitForEchoToBe(bool high);

    /**
     * Gets the length of time that the echo signal is high
     * @returns microseconds that echo is high
     */
    uint64_t _GetEchoHighDuration();

    /**
     * Calculates distance reading from the proximity sensor, in centimeters
     * @returns centimeters
     */
    uint64_t _CalculateDistance(uint64_t duration_us);
};
