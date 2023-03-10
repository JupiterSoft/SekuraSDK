cmake_minimum_required(VERSION 3.5)

project(SekuraSDK VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

add_subdirectory(libSekura)
include_directories(libSekura)

set(PROJECT_SOURCES main.cpp systemcommandform.h systemcommandform.cpp systemcommandform.ui)

if(APPLE)
  set(MACOSX_BUNDLE_ICON_FILE sekura.icns)
  set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/images/sekura.icns")
  set_source_files_properties(${app_icon_macos}
                              PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32)
  set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/images/resource.rc")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SekuraSDK
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_macos}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SekuraSDK APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SekuraSDK SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SekuraSDK
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(SekuraSDK PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network libSekura)

set_target_properties(SekuraSDK PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER sdk.jupitersoft.kz
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SekuraSDK
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SekuraSDK)
endif()
