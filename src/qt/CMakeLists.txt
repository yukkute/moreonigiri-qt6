# Copyright (c) 2022-2023 yukkute
# This is the FLOSS software released under MIT License: see LICENSE.md
#  
# SPDX-License-Identifier: MIT

#  +====================+
#  |     ONIGIRI_QT     |
#  +====================+

find_package(Qt6 COMPONENTS Core Gui Widgets Svg REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB onigiri_qt_code *.cpp *.hpp)

list (APPEND RESOURCES resources.qrc)
qt_add_resources(onigiri_qt_images ${RESOURCES})

#qt_add_library(onigiri_qt STATIC ${onigiri_qt_code}
# ${onigiri_qt_images}
#)

qt_add_executable(onigiri_qt ${onigiri_qt_code} ${onigiri_qt_images})

if(FALLBACK_IMG)
  target_compile_definitions(onigiri_qt PUBLIC "FALLBACK_IMG=true")
else()
  target_compile_definitions(onigiri_qt PUBLIC "FALLBACK_IMG=false")
endif()

target_link_libraries(onigiri_qt PRIVATE Qt6::Core Qt6::Widgets Qt6::Svg)
target_link_libraries(onigiri_qt PUBLIC onigiri_logic)