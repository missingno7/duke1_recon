# duke1: the SDL3 port.  One executable that plays all three episodes: src/ is translated
# once per episode by tools/port_gen.py (into build/port-gen/epN, never committed) and
# compiled together with the emulated PC (platform) below.
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
set(SDL3_ROOT "C:/tools/sdl3-3.4.16-mingw/SDL3-3.4.16/x86_64-w64-mingw32" CACHE PATH "SDL3 installation")
set(SDL3_DIR "${SDL3_ROOT}/lib/cmake/SDL3" CACHE PATH "SDL3 package")

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

# ---- the game: src/ translated per episode ----
file(GLOB GAME_SOURCE_FILES CONFIGURE_DEPENDS "${REPO_ROOT}/src/*.C" "${REPO_ROOT}/src/*.H"
     "${REPO_ROOT}/src/*.c" "${REPO_ROOT}/src/*.h")
file(GLOB OVERRIDE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/override/*.c")

set(GENERATED_FILES)
set(EPISODE_SOURCES)
foreach(ep RANGE 1 3)
  list(APPEND GENERATED_FILES "${PORT_GEN_DIR}/ep${ep}/DUKE.H"
                              "${PORT_GEN_DIR}/ep${ep}/GAME1.C" "${PORT_GEN_DIR}/ep${ep}/GAME2.C")
  list(APPEND EPISODE_SOURCES "${PORT_GEN_DIR}/ep${ep}/GAME1.C" "${PORT_GEN_DIR}/ep${ep}/GAME2.C")
  # Turbo C semantics: unsigned char (-K), wrapping 16-bit arithmetic; -O0 because the game
  # busy-waits on globals that its interrupt handlers change.
  set_source_files_properties("${PORT_GEN_DIR}/ep${ep}/GAME1.C" "${PORT_GEN_DIR}/ep${ep}/GAME2.C"
    PROPERTIES LANGUAGE C
               COMPILE_DEFINITIONS "EPISODE=${ep}"
               COMPILE_OPTIONS "-O0;-fwrapv;-fno-strict-aliasing;-funsigned-char;-x;c")
endforeach()
set_source_files_properties(${GENERATED_FILES} PROPERTIES GENERATED TRUE)

add_custom_command(
  OUTPUT ${GENERATED_FILES}
  COMMAND "${Python3_EXECUTABLE}" "${REPO_ROOT}/tools/port_gen.py"
          --source "${REPO_ROOT}/src" --output "${PORT_GEN_DIR}"
          --override-dir "${CMAKE_CURRENT_SOURCE_DIR}/override"
  DEPENDS "${REPO_ROOT}/tools/port_gen.py" ${GAME_SOURCE_FILES} ${OVERRIDE_FILES}
  VERBATIM)
add_custom_target(port_sources DEPENDS ${GENERATED_FILES})

# ---- the emulated PC ----
set(PLATFORM_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/launcher.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_sdl.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_interrupt.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_io.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_speaker.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/pc_dos.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/vga.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/toolbox.c")
set_source_files_properties(${PLATFORM_SOURCES}
  PROPERTIES COMPILE_OPTIONS "-O2;-fwrapv;-fno-strict-aliasing;-funsigned-char")

add_executable(duke1 ${EPISODE_SOURCES} ${PLATFORM_SOURCES})
add_dependencies(duke1 port_sources)
target_include_directories(duke1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(duke1 PRIVATE SDL3::SDL3)
if(MINGW)
  # Drop-in build: a window application with the MinGW runtime linked in, so only SDL3.dll
  # has to sit next to duke1.exe; messages go to duke1.log.
  target_link_options(duke1 PRIVATE -mwindows -static)
endif()
set_target_properties(duke1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_custom_command(TARGET duke1 POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${SDL3_ROOT}/bin/SDL3.dll" "$<TARGET_FILE_DIR:duke1>/SDL3.dll"
  VERBATIM)

# ---- the EGA self-test (tools/validate.py runs it) ----
add_executable(vga_selftest "${CMAKE_CURRENT_SOURCE_DIR}/tests/vga_selftest.c"
                            "${CMAKE_CURRENT_SOURCE_DIR}/vga.c" "${CMAKE_CURRENT_SOURCE_DIR}/toolbox.c")
target_include_directories(vga_selftest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/tests/vga_selftest.c"
  PROPERTIES COMPILE_OPTIONS "-O2;-funsigned-char")
set_target_properties(vga_selftest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
