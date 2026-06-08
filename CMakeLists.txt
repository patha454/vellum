cmake_minimum_required(VERSION 4.2)
project(vellum C)

set(CMAKE_C_STANDARD 17)

add_library(vellum STATIC
        include/vellum/colour.h
        include/vellum/cell.h
        include/vellum/char.h
        src/irm_framebuffer.c
        include/vellum/canvas.h
        include/vellum/style.h
        src/canvas.c
        include/vellum/framebuffer.h)
target_include_directories(vellum PUBLIC include)
target_compile_features(vellum PUBLIC c_std_17)

