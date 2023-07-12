cmake_minimum_required(VERSION 3.5)

project(PhotoLaboratoryTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set(CMAKE_CXX_FLAGS --coverage)
# set(CMAKE_EXE_LINKER_FLAGS --coverage)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

include_directories(
  ${PROJECT_SOURCE_DIR}/../Controller
  ${PROJECT_SOURCE_DIR}/../Model
  ${PROJECT_SOURCE_DIR}/../Model/FilterModel
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper/FilterManagers
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper/Filters
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper/Filters/ConvolutionFilters
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper/Filters/NonConvolutionFilters
  ${PROJECT_SOURCE_DIR}/../Model/FilterHelper/Filters/ColorCorrectionFilters
)

set(PROJECT_SOURCES
        test.cc
        ../Model/FilterHelper/Filters/ColorCorrectionFilters/colorcorrectionfilters.cc
        ../Model/FilterHelper/Filters/NonConvolutionFilters/nonconvolutionfilters.cc
        ../Model/FilterHelper/Filters/ConvolutionFilters/convolutionfilters.cc
        ../Model/FilterHelper/basefilter.cc
)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    test.cc
    ${PROJECT_SOURCES}
)

qt_add_resources(${PROJECT_NAME} "images"
    PREFIX "/"
    BASE "../../misc/test_images"
    FILES
    ../../misc/test_images/test_original.png
    ../../misc/test_images/test_original2.png
    ../../misc/test_images/test_grayscale.png
    ../../misc/test_images/test_negative.png
    ../../misc/test_images/test_toning.png
    ../../misc/test_images/test_emboss.png
    ../../misc/test_images/test_sharpen.png
    ../../misc/test_images/test_boxblur.png
    ../../misc/test_images/test_gaussianblur.png
    ../../misc/test_images/test_laplacian.png
    ../../misc/test_images/test_prewitt.png
    ../../misc/test_images/test_kernel.png
    ../../misc/test_images/test_bright.png
    ../../misc/test_images/test_contrast.png
    ../../misc/test_images/test_hslv_0_255_130.png
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})