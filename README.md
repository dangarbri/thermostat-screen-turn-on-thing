# Thermostat Turner Onner
This is a project to program a Raspberry Pico to
physically turn on my thermostat touch screen as
I walk by it.

Includes:
 - Re-usable Servo Driver (complete, though a bit flakey)
 - Proximity/Sonic sensor Driver (not implemented)
 - Main code to read sensor and turn servo

Of use to general hobbyists may be the pwm servo driver.
I couldn't find a reliable one that made sense. The
one I've written here is fully documented explaining
how PWM is controlled at 50Hz for my servo (SG92R)

