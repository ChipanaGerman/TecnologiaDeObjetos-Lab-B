# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Ejercicio2_Task_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Ejercicio2_Task_autogen.dir\\ParseCache.txt"
  "Ejercicio2_Task_autogen"
  )
endif()
