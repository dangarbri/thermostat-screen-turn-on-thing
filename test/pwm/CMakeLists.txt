add_executable(pwm_test
    main.cpp
    ../../src/pwm.cpp
)

add_compile_definitions(DEBUG_PWM)

pico_enable_stdio_usb(pwm_test 1)
pico_enable_stdio_uart(pwm_test 0)

pico_add_extra_outputs(pwm_test)

target_link_libraries(pwm_test pico_stdlib hardware_pwm hardware_clocks)

