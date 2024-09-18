################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
# following copyright and licenses apply:
#
# Copyright 2024 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################
cmake_minimum_required(VERSION 3.3)


list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(PkgConfig REQUIRED) 

pkg_check_modules(GSTREAMERBASE REQUIRED gstreamer-app-1.0)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# find_package(GStreamer REQUIRED)

# Build system audio platform library
set(Platform_SOURCES
        systemaudioplatform.cpp
        logger.cpp
   )
add_library(systemaudioplatform  SHARED ${Platform_SOURCES})

set(AUDIO_CLIENT_LIB "RtkHALMisc")


target_include_directories(systemaudioplatform PRIVATE ${GSTREAMER_INCLUDES})
target_include_directories(systemaudioplatform PRIVATE ${GSTREAMERBASE_INCLUDE_DIRS})

target_link_libraries(systemaudioplatform PRIVATE ${GSTREAMER_LIBRARIES})
target_link_libraries(systemaudioplatform PRIVATE ${GSTREAMERBASE_LIBRARIES})
target_link_libraries(systemaudioplatform PRIVATE ${AUDIO_CLIENT_LIB})


install(TARGETS systemaudioplatform LIBRARY DESTINATION lib)
install(FILES systemaudioplatform.h DESTINATION include)
