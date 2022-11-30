# Copyright (c) 2022-2023 yukkute
# This is the FLOSS software released under MIT License: see LICENSE.md
#  
# SPDX-License-Identifier: MIT

#  +=========================+
#  |     MOREONIGIRI_QT66     |
#  +=========================+

find_package(Qt6 COMPONENTS Core Gui Widgets Svg REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB moreonigiri_qt6_code *.cpp *.hpp)

list (APPEND RESOURCES resources.qrc)
qt_add_resources(moreonigiri_qt6_images ${RESOURCES})

qt_add_executable(moreonigiri_qt6 ${moreonigiri_qt6_code} ${moreonigiri_qt6_images})

if(FALLBACK_IMG)
  target_compile_definitions(moreonigiri_qt6 PUBLIC "FALLBACK_IMG=true")
else()
  target_compile_definitions(moreonigiri_qt6 PUBLIC "FALLBACK_IMG=false")
endif()

target_link_libraries(moreonigiri_qt6 PRIVATE Qt6::Core Qt6::Widgets Qt6::Svg)
target_link_libraries(moreonigiri_qt6 PUBLIC moreonigiri_flow)