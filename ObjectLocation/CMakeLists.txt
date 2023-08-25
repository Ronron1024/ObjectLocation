# CMakeList.txt : CMake project for ObjectLocation, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ObjectLocation "ObjectLocation.cpp" "ObjectLocation.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ObjectLocation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
