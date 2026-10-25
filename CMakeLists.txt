cmake_minimum_required(VERSION 3.24)
project(igi2 LANGUAGES C RC)

# The game is a 32-bit Windows program; configure with:  cmake -B build/cmake -A Win32
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "IGI 2 builds as 32-bit only: configure with -A Win32")
endif()

# DirectX 8.1 SDK (d3d8.lib, d3dx8.lib): the Windows SDK no longer ships them
set(DX8_SDK "E:/.sdks/DXF" CACHE PATH "DirectX 8.1 SDK root")

file(GLOB_RECURSE IGI2_SOURCES CONFIGURE_DEPENDS src/*.c data/*.c support/*.c)

add_executable(igi2 WIN32 ${IGI2_SOURCES} res/igi2.rc)
target_include_directories(igi2 PRIVATE include)

# A debugging heap: every game allocation ends at an inaccessible page (support/guardheap.c)
option(IGI2_GUARD_HEAP "Catch heap overruns where they happen" OFF)
if(IGI2_GUARD_HEAP)
    target_compile_definitions(igi2 PRIVATE IGI2_GUARD_HEAP)
endif()
set_target_properties(igi2 PROPERTIES C_STANDARD 17 C_STANDARD_REQUIRED ON)

target_compile_options(igi2 PRIVATE
    $<$<COMPILE_LANGUAGE:C>:/arch:IA32>   # x87 floating point, as the original
    $<$<COMPILE_LANGUAGE:C>:/fp:precise>
    $<$<COMPILE_LANGUAGE:C>:/Oy->         # keep frame pointers: easier side-by-side debugging
    $<$<COMPILE_LANGUAGE:C>:/permissive>
    $<$<COMPILE_LANGUAGE:C>:/W1>
    $<$<COMPILE_LANGUAGE:C>:/Zi>          # a PDB in every configuration: crashes name the function
    $<$<COMPILE_LANGUAGE:C>:/MP>          # one project of ~500 files: compile them in parallel
)

# every generated file includes igi2.h (2.9 MB of types, prototypes and globals): parse it once.
# guardheap.c is the allocator igi2.h redirects malloc to, so it must not see that header
target_precompile_headers(igi2 PRIVATE include/igi2.h)
set_source_files_properties(support/guardheap.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# Retail fallback (support/fallback.c): IGI2_FALLBACK=<functions> runs those as the original
# machine code. Entries must be hot-patchable, every call must reach the entry (no inlining), and
# no two functions may share code (no identical-code folding).
option(IGI2_FALLBACK "Let IGI2_FALLBACK send chosen functions to the retail code" ON)
if(IGI2_FALLBACK)
    target_compile_definitions(igi2 PRIVATE IGI2_FALLBACK)
    target_compile_options(igi2 PRIVATE $<$<COMPILE_LANGUAGE:C>:/hotpatch> $<$<COMPILE_LANGUAGE:C>:/Ob0>)
    target_link_options(igi2 PRIVATE /FUNCTIONPADMIN:5 /OPT:NOICF)
endif()
# it allocates with the C runtime directly: igi2.h's guard-heap redirection must not reach it
set_source_files_properties(support/fallback.c data/fallback_crt.c support/replay_host.c support/fpu.c support/qtask_asm.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# the retail image the globals live in (build/image.bin, made by tools/export_data.py)
set_source_files_properties(res/igi2.rc PROPERTIES OBJECT_DEPENDS ${CMAKE_SOURCE_DIR}/build/image.bin)

target_link_libraries(igi2 PRIVATE
    kernel32 user32 gdi32 advapi32 ole32 winmm version wsock32 wininet
    dinput8 dsound dxguid
    ${DX8_SDK}/lib/d3d8.lib
    ${DX8_SDK}/lib/d3dx8.lib
    ${CMAKE_SOURCE_DIR}/third_party/lib/mss32.lib
    legacy_stdio_definitions   # d3dx8.lib was built against the old C runtime's stdio
)
# The retail image goes back to its own addresses, 0x400000 and up (data/data_init.c): the exe
# is based below it, at a fixed address, so its code ends before 0x400000 and the reserved
# section that follows covers the retail range.
target_link_options(igi2 PRIVATE /SAFESEH:NO /LARGEADDRESSAWARE:NO /BASE:0x10000 /FIXED /DYNAMICBASE:NO
    /DEBUG /OPT:REF)
if(NOT IGI2_FALLBACK)
    target_link_options(igi2 PRIVATE /OPT:ICF)  # identical functions share code: only without the fallback
endif()
