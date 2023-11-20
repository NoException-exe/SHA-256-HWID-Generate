
add_executable (HwidHash "HwidHash.cpp" "HwidHash.h" "hwid/hwid.cpp" "lib/picosha2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HwidHash PROPERTY CXX_STANDARD 20)
endif()

