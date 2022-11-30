# Copyright (c) 2022-2023 yukkute
# This is the FLOSS software released under MIT License: see LICENSE.md
#  
# SPDX-License-Identifier: MIT

#  +============================+
#  |      MOREONIGIRI_QT6       |
#  +============================+

add_subdirectory(qt)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
