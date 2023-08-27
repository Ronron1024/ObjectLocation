set(LIBRARY_DIR "C:\\Program Files (x86)\\Intel RealSense SDK 2.0\\lib\\x64")
set(DLL_DIR "C:\\Program Files (x86)\\Intel RealSense SDK 2.0\\bin\\x64")
set(ADDITIONAL_INCLUDE_DIRS "C:\\Program Files (x86)\\Intel RealSense SDK 2.0\\include")

find_library(REALSENSE2_FOUND realsense2 HINTS ${LIBRARY_DIR} REQUIRED)
if(NOT REALSENSE2_FOUND)
	set(REALSENSE2_FOUND "realsense2")
	message(warn "Failed to find realsense2")
endif()

find_package(PCL 1.3 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ObjectLocation "ObjectLocation.cpp" "ObjectLocation.h")
include_directories(ObjectLocation ${ADDITIONAL_INCLUDE_DIRS})
target_link_libraries(ObjectLocation ${REALSENSE2_FOUND})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ObjectLocation PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ObjectLocation ${PCL_LIBRARIES})