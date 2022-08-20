#include "servo.h"

Servo::Servo(uint pin) {
    _pin = pin;
    gpio_init(_pin);
    gpio_set_dir(_pin, GPIO_OUT);
}

void Servo::on() {
    gpio_put(_pin, 1);
}

void Servo::off() {
    gpio_put(_pin, 0);
}

