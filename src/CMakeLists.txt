cmake_minimum_required(VERSION 3.5)

project(PhotoLaboratory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(
  ${CMAKE_SOURCE_DIR}/View
  ${CMAKE_SOURCE_DIR}/Controller
  ${CMAKE_SOURCE_DIR}/Model
  ${CMAKE_SOURCE_DIR}/Model/FilterModel
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper/FilterManagers
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper/Filters
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper/Filters/ConvolutionFilters
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper/Filters/NonConvolutionFilters
  ${CMAKE_SOURCE_DIR}/Model/FilterHelper/Filters/ColorCorrectionFilters
)

set(PROJECT_SOURCES
        main.cc
        View/view.cc
        View/view_help.cc
        View/view.ui
        View/customkernelview.cc
        View/customkernelview.ui
        Model/FilterHelper/Filters/ColorCorrectionFilters/colorcorrectionfilters.cc
        Model/FilterHelper/Filters/NonConvolutionFilters/nonconvolutionfilters.cc
        Model/FilterHelper/Filters/ConvolutionFilters/convolutionfilters.cc
        Model/FilterHelper/basefilter.cc
)

set(MACOSX_BUNDLE_ICON_FILE PhotoLaboratoryIcon.icns)
set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/View/PhotoLaboratoryIcon.icns)
set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PhotoLaboratory
        MANUAL_FINALIZATION
        ${APP_ICON}
        ${PROJECT_SOURCES}
        View/icon.qrc
        View/icon.rc
    )

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(PhotoLaboratory
#        MANUAL_FINALIZATION
#        ${APP_ICON}
#        ${PROJECT_SOURCES}
#        View/icon.qrc
#        View/icon.rc
#    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PhotoLaboratory APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PhotoLaboratory SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PhotoLaboratory
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PhotoLaboratory PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PhotoLaboratory PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PhotoLaboratory
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhotoLaboratory)
endif()
