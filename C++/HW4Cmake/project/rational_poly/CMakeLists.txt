add_executable(rational_poly rational_poly.cpp)

include_directories(../lib_rational)

target_link_libraries(rational_poly lib_rational)