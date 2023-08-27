find_package(PCL 1.3 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ObjectLocation "ObjectLocation.cpp" "ObjectLocation.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ObjectLocation PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ObjectLocation ${PCL_LIBRARIES})