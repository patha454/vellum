cmake_minimum_required(VERSION 4.2)
project(vellum C)

set(CMAKE_C_STANDARD 17)

add_library(vellum STATIC vellum.c
        ve_colour.h
        ve_cell.h
        ve_char.h
        ve_irm_framebuffer.c
        ve_canvas.h
        ve_style.h
        canvas.c
        ve_framebuffer.h)
target_compile_features(vellum PUBLIC c_std_17)
