cmake_minimum_required(VERSION 3.20)
project(VideoF2 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -frecord-gcc-switches -Wall -Wextra -pedantic")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0 REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(CMAKE_PREFIX_PATH /app/3rdparty/cyclonedds-0.10.4/cyclonedds-0.10.4 
                        /app/3rdparty/cyclonedds-0.10.4/cyclonedds-cxx-0.10.4)
find_package(CycloneDDS-CXX REQUIRED)

find_package(gflags REQUIRED)
find_package(glog REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${GTKMM_INCLUDE_DIRS} 
                    ${GST_INCLUDE_DIRS} 
                    ${SWSCALE_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src/
                    ${PROJECT_SOURCE_DIR}/src/mediax/
                    ${PROJECT_SOURCE_DIR}/src/ui/)

link_directories(${GTKMM_LIBRARY_DIRS})

FILE(GLOB_RECURSE APP_SOURCES ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE MEDIAX_SOURCES ${PROJECT_SOURCE_DIR}/src/mediax/*.h ${PROJECT_SOURCE_DIR}/src/mediax/*.cc ${PROJECT_SOURCE_DIR}/src/mediax/*.i)

set(SOURCES ${APP_SOURCES} ${MEDIAX_SOURCES})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES} CycloneDDS-CXX::ddscxx glog::glog  ${GFLAGS_LIBRARIES} ${SWSCALE_LIBRARIES})
