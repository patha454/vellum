cmake_minimum_required(VERSION 4.2)
project(vellum C)

set(CMAKE_C_STANDARD 17)

add_library(vellum STATIC vellum.c
        ve_colour.h
        ve_cell.h
        ve_char.h
        ve_framebuffer.h
        framebuffer.c)
target_compile_features(vellum PUBLIC c_std_17)
