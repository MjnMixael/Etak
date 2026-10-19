# Etemenanki — a translation tool for FreeSpace Open.
#
# Cross-platform (Windows + Linux) CMake build. This replaces the former
# Qt VS Tools .vcxproj: VS 2026 opens this folder directly ("Open Folder"),
# and the same build works on Linux with GCC/Clang.

cmake_minimum_required(VERSION 3.21)

project(Etemenanki
    VERSION 1.6.0
    DESCRIPTION "A translation tool for FreeSpace Open"
    LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets)

# AUTOMOC / AUTOUIC / AUTORCC, sane defaults, GUI app helpers.
qt_standard_project_setup()

qt_add_executable(Etemenanki WIN32
    Etemenanki/main.cpp
    Etemenanki/Etemenanki.cpp
    Etemenanki/Etemenanki.h
    Etemenanki/IgnoreFiles.cpp
    Etemenanki/IgnoreFiles.h
    Etemenanki/IgnoreIds.cpp
    Etemenanki/IgnoreIds.h
    Etemenanki/PreloadPairs.cpp
    Etemenanki/PreloadPairs.h
    Etemenanki/Settings.cpp
    Etemenanki/Settings.h
    Etemenanki/xstr.cpp
    Etemenanki/xstr.h
    Etemenanki/Etemenanki.ui
    Etemenanki/IgnoreFiles.ui
    Etemenanki/IgnoreIds.ui
    Etemenanki/PreloadPairs.ui
    Etemenanki/Settings.ui
    Etemenanki/Etemenanki.qrc
)

target_compile_features(Etemenanki PRIVATE cxx_std_17)

# Make F5 in the generated VS solution launch the app, not the non-runnable
# ALL_BUILD utility target (ignored by non-VS generators).
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Etemenanki)

# The sources include each other and the generated ui_*.h by bare name; this
# also puts the .rc's directory on the resource-compiler include path so its
# "Etemenanki.ico" reference resolves.
target_include_directories(Etemenanki PRIVATE Etemenanki)

target_link_libraries(Etemenanki PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Match the old project's Unicode character set on MSVC.
if(MSVC)
    target_compile_definitions(Etemenanki PRIVATE UNICODE _UNICODE)
endif()

# Windows resource (app icon). Windows-only input; harmless to omit elsewhere.
if(WIN32)
    target_sources(Etemenanki PRIVATE Etemenanki/Etemenanki.rc)
endif()

# Preserve the old post-build behaviour: stage the Qt runtime next to the exe
# so the app runs straight from the build tree (F5 in VS). CI deploys/packages
# separately; this is only a developer convenience.
if(WIN32)
    get_target_property(_qmake_exe Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_exe}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Etemenanki POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations "$<TARGET_FILE:Etemenanki>"
            COMMENT "Deploying Qt runtime with windeployqt"
            VERBATIM)
    endif()
endif()
