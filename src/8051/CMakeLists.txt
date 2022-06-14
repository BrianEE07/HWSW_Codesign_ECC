# check cmake version
cmake_minimum_required(VERSION 3.16)
project(main)

find_package(SystemCLanguage CONFIG REQUIRED)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})


cmake_minimum_required(VERSION 3.0)
project(main)

find_package(SystemCLanguage CONFIG REQUIRED)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})


file(GLOB 8051_SRC
"*.h"
"*.cpp"
)
add_executable(
	${PROJECT_NAME}
	8051_iss.cpp
  core_8051.cpp
  sram.cpp
  Xram.cpp
  top.cpp
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE SystemC::systemc
)

set_property(
	TARGET ${PROJECT_NAME}
	PROPERTY CXX_STANDARD ${SystemC_CXX_STANDARD}
)