cmake_minimum_required(VERSION 3.5.0)
project(ayed VERSION 0.1.0 LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)

# Flags para debug y para deshabilitar optimizaciones
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

set(SOURCES
   # ARchivos fuente a compilar
)

# Define el ejecutable con todos los archivos fuente
add_executable(APP ${SOURCES})