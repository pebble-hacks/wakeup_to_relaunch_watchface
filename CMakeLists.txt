cmake_minimum_required (VERSION 3.2)
project (pebble_app)

set(CMAKE_C_FLAGS "-std=c11 -mthumb -ffunction-sections -g -fno-diagnostics-show-caret -D_REENT_SMALL=1 -Wall -Wextra -Werror -Wpointer-arith -Wno-unused-parameter -Wno-missing-field-initializers -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=unused-but-set-variable -Wno-packed-bitfield-compat -mcpu=cortex-m3 -Os -Werror=return-type")
add_definitions("-DPBL_RECT=1")

file(GLOB_RECURSE src "src/*")
file(GLOB_RECURSE build "build/basalt/*.c")

set(SOURCES
        ${src}
        ${build}
        )

set(INCLUDES
        "~/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble/basalt/include"
        src
        build/basalt
        )

include_directories(${INCLUDES})

add_executable(app ${SOURCES})
