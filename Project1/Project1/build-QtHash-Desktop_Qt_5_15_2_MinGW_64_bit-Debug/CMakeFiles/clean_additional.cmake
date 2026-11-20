# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtHash_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtHash_autogen.dir\\ParseCache.txt"
  "QtHash_autogen"
  )
endif()
