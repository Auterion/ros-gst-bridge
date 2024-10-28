add_library(perfetto-lib
  perfetto.cc
)

# Set -fPIC for this library to support usage in shared libraries
set_target_properties(perfetto-lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(
  perfetto-lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(perfetto::perfetto-lib ALIAS perfetto-lib)