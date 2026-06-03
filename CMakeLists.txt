cmake_minimum_required(VERSION 4.2)
project(vellum C)

set(CMAKE_C_STANDARD 17)

add_library(vellum STATIC library.c)
target_compile_features(vellum PUBLIC c_std_17)
