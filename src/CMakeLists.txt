add_executable(thermostat_turner_onner
    main.cpp
    servo.cpp
    proximity_sensor.cpp
)
pico_enable_stdio_usb(thermostat_turner_onner 1)
pico_enable_stdio_uart(thermostat_turner_onner 0)

pico_add_extra_outputs(thermostat_turner_onner)

target_link_libraries(thermostat_turner_onner pico_stdlib hardware_pwm)

