# Copyright (c) 2022-2023 yukkute
# This is the FLOSS software released under MIT License: see LICENSE.md
#  
# SPDX-License-Identifier: MIT

cmake_policy(SET CMP0048 NEW)
project(onigiri VERSION 1 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.24.3)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  moreonigiri_flow
  GIT_REPOSITORY https://github.com/yukkute/moreonigiri-flow.git
)
FetchContent_MakeAvailable(moreonigiri_flow)

option(BUILD_TESTS  "Build tests" OFF)


add_subdirectory(src)
