cmake_minimum_required(VERSION 3.23)
project(JuceGeometricMedian VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/JUCE)
juce_add_gui_app(JuceGeometricMedian PRODUCT_NAME "Geometric Median")
add_subdirectory(tests)
target_link_libraries(JuceGeometricMedian
        PRIVATE
            juce::juce_core
            juce::juce_gui_basics
        )
add_subdirectory(src/)
target_compile_definitions(JuceGeometricMedian
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CULR=0
            JUCE_APPLICATION_NAME_STRING="Geometric Median"
            JUCE_APPLICATION_VERSION="0.0.1"
        )


add_subdirectory(libs/Catch2)

target_link_libraries(JuceGeometricMedianTests PRIVATE Catch2::Catch2WithMain)
