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
     * Blocking call that will return the average reading from the sensor
     * over 60ms (recommended by the elecfreak's product sheet)
     * 
     * @returns calculated distance in centimeters
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

    /**
     * Gets a readout from the sensor
     * @returns centimeters from the sensor readout
     */
    uint64_t GetSample();
};
