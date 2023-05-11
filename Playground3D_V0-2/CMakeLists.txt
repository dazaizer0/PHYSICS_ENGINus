# CMakeList.txt: projekt CMake dla elementu Playground3D_V0-2, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Playground3D_V0-2")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Playground3D_V0-2 "Playground3D_V0-2.cpp" "Playground3D_V0-2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Playground3D_V0-2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
