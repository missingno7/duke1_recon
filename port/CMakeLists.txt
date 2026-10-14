cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe" CACHE FILEPATH "MinGW-w64 gcc")
endif()

project(duke1_port C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(PORT_GEN_DIR "${REPO_ROOT}/build/port-gen")
set(SDL3_ROOT "C:/tools/sdl3-3.4.16-mingw/SDL3-3.4.16/x86_64-w64-mingw32")
set(SDL3_DIR "${SDL3_ROOT}/lib/cmake/SDL3" CACHE PATH "SDL3 package")

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

file(GLOB PORT_OVERRIDE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/override/*.c")
file(GLOB PORT_VIDEO_IMPLEMENTATIONS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/vga.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/toolbox.c")

set(GENERATED_FILES)
foreach(ep RANGE 1 3)
  list(APPEND GENERATED_FILES
    "${PORT_GEN_DIR}/ep${ep}/DUKE.H"
    "${PORT_GEN_DIR}/ep${ep}/GAME1.C"
    "${PORT_GEN_DIR}/ep${ep}/GAME2.C")
endforeach()

add_custom_command(
  OUTPUT ${GENERATED_FILES}
  COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../tools/port_gen.py"
          --source "${REPO_ROOT}/game" --output "${PORT_GEN_DIR}"
          --override-dir "${CMAKE_CURRENT_SOURCE_DIR}/override"
  DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/../tools/port_gen.py"
    "${REPO_ROOT}/game/DUKE.H"
    "${REPO_ROOT}/game/GAME1.C"
    "${REPO_ROOT}/game/GAME2.C"
    ${PORT_OVERRIDE_FILES}
  VERBATIM)

set(PORT_VIDEO_SOURCES)
if("${CMAKE_CURRENT_SOURCE_DIR}/vga.c" IN_LIST PORT_VIDEO_IMPLEMENTATIONS)
  list(APPEND PORT_VIDEO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vga.c")
else()
  set(PORT_NEED_VGA_STUB 1)
endif()
if("${CMAKE_CURRENT_SOURCE_DIR}/toolbox.c" IN_LIST PORT_VIDEO_IMPLEMENTATIONS)
  list(APPEND PORT_VIDEO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/toolbox.c")
else()
  set(PORT_NEED_TOOLBOX_STUB 1)
endif()
if(PORT_NEED_VGA_STUB OR PORT_NEED_TOOLBOX_STUB)
  list(APPEND PORT_VIDEO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/stub_vga.c")
  set(STUB_VIDEO_DEFINITIONS)
  if(PORT_NEED_VGA_STUB)
    list(APPEND STUB_VIDEO_DEFINITIONS PORT_NEED_VGA_STUB)
  endif()
  if(PORT_NEED_TOOLBOX_STUB)
    list(APPEND STUB_VIDEO_DEFINITIONS PORT_NEED_TOOLBOX_STUB)
  endif()
  set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/stub_vga.c"
    PROPERTIES COMPILE_DEFINITIONS "${STUB_VIDEO_DEFINITIONS}")
endif()

set(EPISODE_SOURCES)
foreach(ep RANGE 1 3)
  list(APPEND EPISODE_SOURCES
    "${PORT_GEN_DIR}/ep${ep}/GAME1.C"
    "${PORT_GEN_DIR}/ep${ep}/GAME2.C")
  set_source_files_properties(
    "${PORT_GEN_DIR}/ep${ep}/GAME1.C"
    "${PORT_GEN_DIR}/ep${ep}/GAME2.C"
    PROPERTIES
      LANGUAGE C
      COMPILE_DEFINITIONS "EPISODE=${ep}"
      COMPILE_OPTIONS "-O0;-fwrapv;-fno-strict-aliasing;-funsigned-char;-x;c")
endforeach()
set_source_files_properties(${GENERATED_FILES} PROPERTIES GENERATED TRUE)

set(PLATFORM_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_io.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_speaker.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_interrupt.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_dos.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_sdl.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/launcher.c"
  ${PORT_VIDEO_SOURCES})
set_source_files_properties(${PLATFORM_SOURCES}
  PROPERTIES COMPILE_OPTIONS "-O2;-fwrapv;-fno-strict-aliasing;-funsigned-char")

add_executable(duke1
  ${EPISODE_SOURCES}
  ${PLATFORM_SOURCES})
add_custom_target(port_sources DEPENDS ${GENERATED_FILES})
add_dependencies(duke1 port_sources)

target_include_directories(duke1 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${PORT_GEN_DIR}/ep1"
  "${PORT_GEN_DIR}/ep2"
  "${PORT_GEN_DIR}/ep3")
target_link_libraries(duke1 PRIVATE SDL3::SDL3)
if(MINGW)
  # A drop-in build: only SDL3.dll next to duke1.exe (no MinGW runtime DLLs), and a window
  # application (no console); --trace output goes to duke1.log.
  target_link_options(duke1 PRIVATE -mwindows -static)
endif()
set_target_properties(duke1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_custom_command(TARGET duke1 POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${SDL3_ROOT}/bin/SDL3.dll" "$<TARGET_FILE_DIR:duke1>/SDL3.dll"
  VERBATIM)
