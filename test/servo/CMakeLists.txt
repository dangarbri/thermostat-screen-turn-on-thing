include_directories(../../src)

add_compile_definitions(DEBUG_PWM DEBUG_SERVO)

add_executable(servo_test
    main.cpp
    ../../src/servo.cpp
    ../../src/pwm.cpp
)
pico_enable_stdio_usb(servo_test 1)
pico_enable_stdio_uart(servo_test 0)

pico_add_extra_outputs(servo_test)

target_link_libraries(servo_test pico_stdlib hardware_pwm)

