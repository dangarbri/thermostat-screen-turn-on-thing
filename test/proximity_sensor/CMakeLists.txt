include_directories(../../src)

add_executable(proximity_test
    main.cpp
    ../../src/proximity_sensor.cpp
)

add_compile_definitions(DEBUG_PROXIMITY_SENSOR)

pico_enable_stdio_usb(proximity_test 1)
pico_enable_stdio_uart(proximity_test 0)

pico_add_extra_outputs(proximity_test)

target_link_libraries(proximity_test pico_stdlib)

