#########################################################################
#
#  CMAKE
#
#########################################################################

###
#  Minimum Version
#  ---------------
#  The CMake version required.
###
cmake_minimum_required(VERSION 3.1)

###
#  CMake Configuration
#  -------------------
#  Configuration settings for CMake.
#
#  NOTE:
#  These settings have to be applied before the project() setting!
###
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)

###
#  Project Info
#  ------------
#  General simple information about our project.
###
project(mrh_app_base VERSION 1.0.0
                     DESCRIPTION "MRH application base project"
                     LANGUAGES CXX)

#########################################################################
#
#  PATHS
#
#########################################################################

###
#  Binary Paths
#  ------------
#  The paths for our created binary file(s).
###
set(BIN_DIR_PATH "${CMAKE_SOURCE_DIR}/bin/")
file(MAKE_DIRECTORY ${BIN_DIR_PATH})

###
#  Build Paths
#  -----------
#  The paths for the cmake build.
###
set(BUILD_DIR_PATH "${CMAKE_SOURCE_DIR}/build/")
file(MAKE_DIRECTORY ${BUILD_DIR_PATH})

###
#  App Source Paths
#  ----------------
#  The paths to the app source files to use.
#  Add OS specific source files in their own list.
###
set(SRC_DIR_PATH_APP "${CMAKE_SOURCE_DIR}/src/App/")

set(SRC_LIST_APP "${SRC_DIR_PATH_APP}/Revision.h"
                 "${SRC_DIR_PATH_APP}/Main.cpp")
                 
set(SRC_LIST_APP_MODULE_HELLOWORLD "${SRC_DIR_PATH_APP}/Module/HelloWorld/HelloWorld.cpp"
                                   "${SRC_DIR_PATH_APP}/Module/HelloWorld/HelloWorld.h")

###
#  Service Source Paths
#  --------------------
#  The paths to the service source files to use.
#  Add OS specific source files in their own list.
###
set(SRC_DIR_PATH_SERVICE "${CMAKE_SOURCE_DIR}/src/Service")

set(SRC_LIST_SERVICE "${SRC_DIR_PATH_SERVICE}/Main.cpp")

###
#  Library Paths
#  -------------
#  The paths to the external libraries to use. 
#  Both the binary and include paths should be set here.
#  Add OS specific libraries in their own lists.
###
set(STATIC_LIB_DIR_PATH "${CMAKE_SOURCE_DIR}/lib/")
set(STATIC_INCLUDE_DIR_PATH "${CMAKE_SOURCE_DIR}/include/")

#set(STATIC_LIB_BIN_LIST_APP "${STATIC_LIB_DIR_PATH}/my_lib.a")
#set(STATIC_LIB_INCLUDE_LIST_APP "${STATIC_INCLUDE_DIR_PATH}/my_lib_headers")
						 
#set(STATIC_LIB_BIN_LIST_SERVICE "${STATIC_LIB_DIR_PATH}/my_lib.a")
#set(STATIC_LIB_INCLUDE_LIST_SERVICE "${STATIC_INCLUDE_DIR_PATH}/my_lib_headers")

#########################################################################
#
#  TARGET
#
#########################################################################

###
#  Target
#  ------
#  The target(s) to build.
#
#  NOTE: 
#  MRH applications are required to be named App.so, 
#  and application services Service.so!
#  They are build as shared objects.
###
add_library(MRH_App SHARED ${SRC_LIST_APP}
                           ${SRC_LIST_APP_MODULE_HELLOWORLD})
set_target_properties(MRH_App
                      PROPERTIES
                      PREFIX ""
                      OUTPUT_NAME "App"
                      SUFFIX ".so"
                      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
                      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
                      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR_PATH})
					  
add_library(MRH_Service SHARED ${SRC_LIST_SERVICE})
set_target_properties(MRH_Service
                      PROPERTIES
                      PREFIX ""
                      OUTPUT_NAME "Service"
                      SUFFIX ".so"
                      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
                      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR_PATH}
                      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR_PATH})

###
#  Required Libraries
#  ------------------
#  Libraries required by this application.
###
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_library(libmrh NAMES mrh REQUIRED)
find_library(libmrhbf NAMES mrhbf REQUIRED)
find_library(libmrhcevs NAMES mrhcevs REQUIRED)
find_library(libmrhab NAMES mrhab REQUIRED)
find_library(libmrhvt NAMES mrhvt REQUIRED)
find_library(libmrhs NAMES mrhs REQUIRED)

#target_include_directories(MRH_App PUBLIC ${STATIC_LIB_INCLUDE_LIST_APP})
#target_include_directories(MRH_Service PUBLIC ${STATIC_LIB_INCLUDE_LIST_SERVICE})

target_link_libraries(MRH_App PUBLIC Threads::Threads)
target_link_libraries(MRH_App PUBLIC mrh)
target_link_libraries(MRH_App PUBLIC mrhab)
target_link_libraries(MRH_App PUBLIC mrhcevs)
target_link_libraries(MRH_App PUBLIC mrhab)
target_link_libraries(MRH_App PUBLIC mrhvt)
#target_link_libraries(MRH_App PUBLIC ${STATIC_LIB_BIN_LIST_APP})

target_link_libraries(MRH_Service PUBLIC mrhs)
#target_link_libraries(MRH_Service PUBLIC ${STATIC_LIB_BIN_LIST_SERVICE})

###
#  Source Definitions
#  ------------------
#  Preprocessor source definitions.
###