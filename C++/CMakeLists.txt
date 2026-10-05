cmake_minimum_required(VERSION 3.14)
project(ValidadorPassword CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_FLAGS MATCHES "--coverage")
    add_link_options(--coverage)
endif()

# Cargar GoogleTest + GoogleMock (desde /usr/src/googletest en Ubuntu o via FetchContent)
if(EXISTS "/usr/src/googletest/CMakeLists.txt")
    add_subdirectory(/usr/src/googletest googletest_build EXCLUDE_FROM_ALL)
else()
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

# 1. Componente TDD básico (Kata)
add_library(validador validador.cpp)
add_executable(test_validador test_validador.cpp)
target_link_libraries(test_validador PRIVATE validador gtest_main)

# 2. Componente de Seguridad con dependencias externas y Dobles de Prueba (Mocks, Stubs, etc.)
add_library(validador_seguridad validador_seguridad.cpp)
add_executable(test_dobles test_dobles.cpp)
target_link_libraries(test_dobles PRIVATE validador_seguridad gmock_main)

include(GoogleTest)
gtest_discover_tests(test_validador)
gtest_discover_tests(test_dobles)
